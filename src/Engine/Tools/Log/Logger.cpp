#include "Engine/Tools/Log/Logger.h"
#include "Engine/Tools/Other/Files.h"


namespace Engine::Tools
{
    std::mutex Logger::mtx;
    std::atomic<Logger *> Logger::instance = nullptr;

    Logger *Logger::GetInstance()
    {
        if (!instance)
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (!instance)
                instance = new Logger();
        }
        return instance;
    }

    Logger::Logger()
    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(Other::GetExecutableDirectory() + "/logs/log.txt", 1024 * 1024 * 5, 3);
        std::vector<spdlog::sink_ptr> sinks{console_sink, rotating_sink};

        logger = std::make_shared<spdlog::logger>("multi_sink", begin(sinks), end(sinks));
        spdlog::register_logger(logger);

        spdlog::set_pattern("%^[%Y-%m-%d %H:%M:%S.%e] [%l] [thread %t] %v%$");

#ifdef NDEBUG
        logger->set_level(spdlog::level::error);
#else
        logger->set_level(spdlog::level::debug);
#endif
    }

    std::shared_ptr<spdlog::logger> Logger::GetLogger() const
    {
        return logger;
    }
}