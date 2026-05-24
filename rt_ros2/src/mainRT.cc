#include <rclcpp/rclcpp.hpp>
#include <cactus_rt/tracing.h>
#include "rt_ros2/nodo_maquina_estados.h"
#include "rt_ros2/nodo_actuador.h"
#include <chrono>
#include <iomanip>
#include <sstream>

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);

    // EN EL EJERCICIO INICIALIZA AQUÍ EL NODO ADQUISIDOR CON PR 90?

    // Tracers para medir latencias
    auto tracer_actuador = std::make_shared<cactus_rt::tracing::ThreadTracer>("actuador");
    auto tracer_maquina  = std::make_shared<cactus_rt::tracing::ThreadTracer>("maquina_estados");

    // Nodos del sistema
    auto nodo_me     = std::make_shared<rt_ros2::NodoMaquinaEstados>(tracer_maquina);
    auto nodo_act    = std::make_shared<rt_ros2::NodoActuador>(tracer_actuador);

    // Tracing
    cactus_rt::tracing::EnableTracing();
    auto trace_aggregator = std::make_unique<cactus_rt::tracing::TraceAggregator>("rt_ros2");

    // Generar timestamp para el nombre del archivo de la traza
    auto timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::stringstream ss;
    ss << "/code/brickpi/trazas/rt_ros2_" << std::put_time(std::localtime(&timestamp), "%d-%m-%Y_%H.%M") << ".perfetto";
    std::string fichero_traza = ss.str();

    // Registramos los tracers y el sink para volcar la traza a un fichero al finalizar la ejecución
    auto volcar_fichero = std::make_shared<cactus_rt::tracing::FileSink>(fichero_traza.c_str());
    trace_aggregator->RegisterSink(volcar_fichero);
    trace_aggregator->RegisterThreadTracer(tracer_maquina);
    trace_aggregator->RegisterThreadTracer(tracer_actuador);
    quill::start();
    trace_aggregator->Start();

    // Separamos nodos en ejecutores rt y best effort
    rclcpp::executors::SingleThreadedExecutor real_time_executor;
    rclcpp::executors::SingleThreadedExecutor best_effort_executor;
   
    // Añadimos nodos que queramos que sean best effort
    //best_effort_executor.add_node(nodo_me);

    // Añadimos nodos que queramos que sean real time
    real_time_executor.add_node(nodo_act);
    real_time_executor.add_node(nodo_me);

    // Launch real-time Executor in a thread
    std::thread real_time_thread([&real_time_executor]() {
        sched_param sch;
        sch.sched_priority = 60;
        if (sched_setscheduler(0, SCHED_FIFO, &sch) == -1) {
            perror("sched_setscheduler failed");
            exit(-1);
        }
        real_time_executor.spin();
    });

    best_effort_executor.spin();
    
    rclcpp::shutdown();

    cactus_rt::tracing::DisableTracing();
    trace_aggregator->RequestStop();
    trace_aggregator->Join();

    return 0;
}