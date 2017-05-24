// vs-service.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <cpp-defender/configure.h>
#include "main.h"
#include "service.h"
int main(int argc, char* argv[])
{
	//������ �x�������
    boost::program_options::options_description opts("demo options");

    //���x Ҫ������ ����
    opts.add_options()
    ("help,h","show params help")
    ("service,s", "run as service")
    ("install,i","install service")
    ("uninstall,u","uninstall service")
    ;
    //��������
    boost::program_options::variables_map params;
    boost::program_options::store(boost::program_options::parse_command_line(argc,argv,opts),params);

    //�@ʾ����
    if(params.count("help"))
    {
        std::cout<<opts<<"\n";
        return 0;
    }

    //���d����
    service& s = service::get_mutable_instance();
    if(!s.load())
    {
        return 1;
    }

    //��������
    if(params.count("install"))
    {
        KING_TRACE("install service")
        return s.install();
    }
    else if(params.count("uninstall"))
    {
        KING_TRACE("uninstall service")
        return s.uninstall();
    }


    //�\�� ����
    if(params.count("service"))
    {
        KING_TRACE("run as service")
        return service_main();
    }
    else
    {
        KING_TRACE("run normal")
        return normal_main();
    }
    return 0;
}

