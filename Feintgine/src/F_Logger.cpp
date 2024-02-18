#include "F_Logger.h"

namespace Feintgine
{
    F_Logger *F_Logger::p_Instance = 0;

    F_Logger::F_Logger()
    {
    }

    F_Logger::~F_Logger()
    {
       
       closeLog();
    }

    void F_Logger::closeLog()
    {
        if (m_isCreatedLog)
        {
            if(m_logFile)
            {
                m_logFile->close();
            }
           
        }
         std::cout << "close file \n";
    }

    void F_Logger::writeLog(const std::string & log)
    {
        if (!m_isCreatedLog)
        {
            m_logName = "./FeintgineLog.txt";

           std::ofstream strm = std::ofstream("./FeintgineLog.txt",std::ios::trunc);
            strm << "Feintgine log" << "\n";
            //m_logFile = &strm;
            m_isCreatedLog = true;
            strm.close();
           
        }
        else
        {
            std::ofstream strm = std::ofstream("./FeintgineLog.txt",std::ios_base::app);
            strm << log << "\n";
            strm.close();

        }
    }
}