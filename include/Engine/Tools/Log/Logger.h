#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/async.h>
#include <memory>
#include <mutex>

namespace Engine::Tools
{
    class Logger
    {
        enum LogLevel
        {
            Debug,
            Info,
            Warn,
            Error,
            Critical
        };

    public:
        static Logger *GetInstance();

        Logger(const Logger &) = delete;
        Logger(Logger &&) = delete;
        Logger &operator=(const Logger &) = delete;
        Logger &operator=(Logger &&) = delete;

    private:
        Logger();

    private:
        static Logger* instance;

    public:
        std::shared_ptr<spdlog::logger> GetMainLogger() const;
        std::shared_ptr<spdlog::logger> GetErrorLogger() const;

    private:
        std::shared_ptr<spdlog::logger> mainLogger;
        std::shared_ptr<spdlog::logger> errorLogger;
        std::shared_ptr<spdlog::details::thread_pool> tpMain;
        std::shared_ptr<spdlog::details::thread_pool> tpError;
    };
}

#define LOG_TRACE(...)      SPDLOG_LOGGER_TRACE(        ::Engine::Tools::Logger::GetInstance()->GetMainLogger().get(), __VA_ARGS__)
#define LOG_DEBUG(...)      SPDLOG_LOGGER_DEBUG(        ::Engine::Tools::Logger::GetInstance()->GetMainLogger().get(), __VA_ARGS__)
#define LOG_INFO(...)       SPDLOG_LOGGER_INFO(         ::Engine::Tools::Logger::GetInstance()->GetMainLogger().get(), __VA_ARGS__)
#define LOG_WARN(...)       SPDLOG_LOGGER_WARN(         ::Engine::Tools::Logger::GetInstance()->GetMainLogger().get(), __VA_ARGS__)
#define LOG_ERROR(...)      SPDLOG_LOGGER_ERROR(        ::Engine::Tools::Logger::GetInstance()->GetErrorLogger().get(), __VA_ARGS__)
#define LOG_CRITICAL(...)   SPDLOG_LOGGER_CRITICAL(     ::Engine::Tools::Logger::GetInstance()->GetErrorLogger().get(), __VA_ARGS__)