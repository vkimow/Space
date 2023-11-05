#include "Engine/Tools/Log/Logger.h"
#include "Engine/Tools/Other/Files.h"


namespace Engine::Tools
{
    Logger *Logger::instance = nullptr;

    Logger *Logger::GetInstance()
    {
        if (!instance)
        {
            instance = new Logger();
        }
        return instance;
    }

    Logger::Logger()
    {
        auto main_file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(Files::GetExecutableDirectory() + "/logs/main.txt", true);
        main_file_sink->set_pattern("%^[%D %H:%M:%S.%e] [%l] [thread %t] [%g::%!()::%#] %v%$");
        main_file_sink->set_level(spdlog::level::trace);
        auto error_file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(Files::GetExecutableDirectory() + "/logs/errors.txt", true);
        error_file_sink->set_pattern("%^[%D %H:%M:%S.%e] [%l] [thread %t] [%g::%!()::%#] %v%$");
        error_file_sink->set_level(spdlog::level::err);
#ifdef NDEBUG
        std::vector<spdlog::sink_ptr> mainSinks{main_file_sink};
        std::vector<spdlog::sink_ptr> errorSinks{error_file_sink};
#else
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_pattern("%^[%l] [%s::%!()::%#] %v%$");
        console_sink->set_level(spdlog::level::trace);
        std::vector<spdlog::sink_ptr> mainSinks{console_sink, main_file_sink};
        std::vector<spdlog::sink_ptr> errorSinks{console_sink, error_file_sink};
#endif

#ifdef NDEBUG
        tpMain = std::make_shared<spdlog::details::thread_pool>(1028, 1);
        mainLogger = std::make_shared<spdlog::async_logger>("main_logger", mainSinks.begin(), mainSinks.end(), tpMain, spdlog::async_overflow_policy::block);

        tpError = std::make_shared<spdlog::details::thread_pool>(256, 1);
        errorLogger = std::make_shared<spdlog::async_logger>("error_logger", errorSinks.begin(), errorSinks.end(), tpError, spdlog::async_overflow_policy::block);
#else
        mainLogger = std::make_shared<spdlog::logger>("main_logger", mainSinks.begin(), mainSinks.end());
        errorLogger = std::make_shared<spdlog::logger>("error_logger", errorSinks.begin(), errorSinks.end());
#endif

        spdlog::register_logger(mainLogger);
        spdlog::register_logger(errorLogger);
        spdlog::set_level(spdlog::level::trace);
    }

    std::shared_ptr<spdlog::logger> Logger::GetMainLogger() const
    {
        return mainLogger;
    }

    std::shared_ptr<spdlog::logger> Logger::GetErrorLogger() const
    {
        return errorLogger;
    }
}