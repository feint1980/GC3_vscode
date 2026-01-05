

#ifndef SERVERDATAREGISTER_H
#define SERVERDATAREGISTER_H


class ServerDataRegister
{
public:
    static ServerDataRegister* GetInstance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new ServerDataRegister();
        }
        return m_instance;
    }

private:
    static ServerDataRegister* m_instance;
};


#endif // SERVERDATAREGISTER_H