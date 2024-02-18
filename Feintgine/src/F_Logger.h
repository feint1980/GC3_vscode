#pragma once 
#include <iostream>
#include <fstream>

namespace Feintgine
{
    class F_Logger
    {
        public:
        F_Logger();
        ~F_Logger();

        void createLog(const std::string &logName);

        void writeLog(const std::string &log);

        void closeLog();

        static F_Logger *Instance()
        {
            if (p_Instance == 0)
            {
                p_Instance = new F_Logger;
                return p_Instance;
            }
            return p_Instance;
        }

        private:

        bool m_isCreatedLog = false;

        std::ofstream * m_logFile;

        static F_Logger *p_Instance;
        std::string m_logName;
   
    };
}