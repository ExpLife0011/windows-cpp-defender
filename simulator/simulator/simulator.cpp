// simulator.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#define KG_DEBUG_USE_DEBUG
//�Զ��x ���Iݔ��λ��
std::ofstream outf("simulator.log",std::ios::out|std::ios::trunc);
class out_t
{
public:
	//���Fݔ��
	template<typename T>
	out_t& operator<<(const T& t)
	{
		std::cout<<t;
		outf<<t;
		return *this;
	}

	//���Fˢ�¾��n�^
	void flush()
	{
		std::cout.flush();
	}
};
out_t _kg_logout;
#define KG_DEBUG_STREAM   _kg_logout
#include <kg/debug.hpp>
//ctrl ̎����
BOOL WINAPI CtrlHandler(DWORD fdwCtrlType) ;

//ģ�M ���� ����
boost::thread* g_thread = NULL;
void work_thread();

int main()
{
    std::ofstream out;
    out<<std::endl;
    out.flush();
    //�]�� ctrl ̎����
    if(SetConsoleCtrlHandler(CtrlHandler, TRUE ) )
    {

        KG_INFO("SetConsoleCtrlHandler success")
        boost::thread t(work_thread);
        g_thread = &t;
        t.join();
        KG_INFO("exit ok")
    }
    else
    {
        KG_INFO("SetConsoleCtrlHandler error")
        return 1;
    }
    return 0;
}
void work_thread()
{
    KG_TRACE("work_thread start")
    try
    {
        while(true)
        {
            boost::this_thread::sleep(boost::posix_time::seconds(1));
            KG_INFO("at work")
        }
    }
    catch(boost::thread_interrupted&)
    {
        std::cout<<"thread is end"<<std::endl;
    }
    KG_TRACE("work_thread stop")
}
BOOL WINAPI CtrlHandler(DWORD fdwCtrlType)
{
    KG_INFO("fdwCtrlType = "<<fdwCtrlType)
    switch( fdwCtrlType )
    {
    case CTRL_C_EVENT:
        KG_INFO("CTRL_C_EVENT")
        if(g_thread)
        {
            g_thread->interrupt();
            g_thread->join();
            return TRUE;
        }
        return FALSE;
    case CTRL_CLOSE_EVENT:
        KG_INFO("CTRL_CLOSE_EVENT")
        if(g_thread)
        {
            g_thread->interrupt();
            g_thread->join();
        }
        return FALSE;
    case CTRL_LOGOFF_EVENT:
        KG_INFO("CTRL_LOGOFF_EVENT")
        if(g_thread)
        {
            g_thread->interrupt();
            g_thread->join();
        }
        return FALSE;
    case CTRL_SHUTDOWN_EVENT:
        KG_INFO("CTRL_SHUTDOWN_EVENT")
        if(g_thread)
        {
            g_thread->interrupt();
            g_thread->join();
        }
        return FALSE;
    }
    return FALSE;
}

