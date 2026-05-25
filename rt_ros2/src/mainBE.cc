#include <rclcpp/rclcpp.hpp>
#include <cactus_rt/tracing.h>
#include "rt_ros2/nodo_maquina_estados.h"
#include "rt_ros2/nodo_actuador.h"
#include "rt_ros2/nodo_ruido.h"
#include <chrono>
#include <iomanip>
#include <sstream>

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);

    // Tracers para medir latencias
    auto tracer_actuador = std::make_shared<cactus_rt::tracing::ThreadTracer>("actuador");
    auto tracer_maquina  = std::make_shared<cactus_rt::tracing::ThreadTracer>("maquina_estados");
    auto tracer_ruido    = std::make_shared<cactus_rt::tracing::ThreadTracer>("ruido");

    // Nodos del sistema
    auto nodo_me     = std::make_shared<rt_ros2::NodoMaquinaEstados>(tracer_maquina);
    auto nodo_act    = std::make_shared<rt_ros2::NodoActuador>(tracer_actuador);
    auto nodo_ruido  = std::make_shared<rt_ros2::NodoRuido>(tracer_ruido);

    // Tracing
    cactus_rt::tracing::EnableTracing();
    auto trace_aggregator = std::make_unique<cactus_rt::tracing::TraceAggregator>("rt_ros2");

    // Generar timestamp para el nombre del archivo
    auto timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::stringstream ss;
    ss << "/code/brickpi/trazas/rt_ros2_" << std::put_time(std::localtime(&timestamp), "%d-%m-%Y_%H:%M") << ".perfetto";
    std::string fichero_traza = ss.str();

    auto volcar_fichero = std::make_shared<cactus_rt::tracing::FileSink>(fichero_traza.c_str());
    trace_aggregator->RegisterSink(volcar_fichero);
    trace_aggregator->RegisterThreadTracer(tracer_maquina);
    trace_aggregator->RegisterThreadTracer(tracer_actuador);
    trace_aggregator->RegisterThreadTracer(tracer_ruido);
    quill::start();
    trace_aggregator->Start();

    // Todos los nodos en un mismo ejecutor
    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(nodo_me);
    executor.add_node(nodo_act);
    executor.add_node(nodo_ruido);

    // Forzamos al ejecutor a ejecutarse en la cpu 1
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(1, &cpuset);
    pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);

    executor.spin();

    rclcpp::shutdown();

    cactus_rt::tracing::DisableTracing();
    trace_aggregator->RequestStop();
    trace_aggregator->Join();

    return 0;
}