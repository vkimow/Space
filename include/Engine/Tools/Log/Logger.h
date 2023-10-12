#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <memory>
#include <mutex>

namespace Engine::Tools
{
    class Logger
    {
    public:
        static Logger *GetInstance();

        Logger(const Logger &) = delete;
        Logger(Logger &&) = delete;
        Logger &operator=(const Logger &) = delete;
        Logger &operator=(Logger &&) = delete;

    private:
        Logger();

    private:
        static std::mutex mtx;
        static std::atomic<Logger *> instance;

    public:
        std::shared_ptr<spdlog::logger> GetLogger() const;

    private:
        std::shared_ptr<spdlog::logger> logger;
    };
}

#define LOG_TRACE(...) Engine::Tools::Logger::GetInstance()->GetLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...) Engine::Tools::Logger::GetInstance()->GetLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...) Engine::Tools::Logger::GetInstance()->GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) Engine::Tools::Logger::GetInstance()->GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Engine::Tools::Logger::GetInstance()->GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) Engine::Tools::Logger::GetInstance()->GetLogger()->critical(__VA_ARGS__)