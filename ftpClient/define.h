#pragma once





#define ArraySize(ptr)		(sizeof(ptr) / sizeof(ptr[0]))
#define B2b(returnValue)	(returnValue) == TRUE ? true : false

#define FTP_API                     int
#define FTP_DEFAULT_PORT            21                              //FTPĬ�϶˿ں�  
#define FTP_DEFAULT_BUFFER          1024*4                          //FTP���ػ���Ĭ�ϴ�С  
#define FTP_DEFAULT_PATH            "/mnt/dvs/"                     //FTPĬ�ϱ���·��  

#define FTP_COMMAND_BASE            1000  
#define FTP_COMMAND_END             FTP_COMMAND_BASE + 30  
#define FTP_COMMAND_USERNAME        FTP_COMMAND_BASE + 1            //�û���  
#define FTP_COMMAND_PASSWORD        FTP_COMMAND_BASE + 2            //����  
#define FTP_COMMAND_QUIT            FTP_COMMAND_BASE + 3            //�˳�  
#define FTP_COMMAND_CURRENT_PATH    FTP_COMMAND_BASE + 4            // ��ȡ�ļ�·��  
#define FTP_COMMAND_TYPE_MODE       FTP_COMMAND_BASE + 5            // �ı䴫��ģʽ  
#define FTP_COMMAND_PSAV_MODE       FTP_COMMAND_BASE + 6            // �����˿�ģʽ  
#define FTP_COMMAND_DIR             FTP_COMMAND_BASE + 7            // ��ȡ�ļ��б�  
#define FTP_COMMAND_CHANGE_DIRECTORY FTP_COMMAND_BASE + 8           // �ı�·��  
#define FTP_COMMAND_DELETE_FILE     FTP_COMMAND_BASE + 9            // ɾ���ļ�  
#define FTP_COMMAND_DELETE_DIRECTORY FTP_COMMAND_BASE + 10          // ɾ��Ŀ¼/�ļ���  
#define FTP_COMMAND_CREATE_DIRECTORY FTP_COMMAND_BASE + 11          // ����Ŀ¼/�ļ���  
#define FTP_COMMAND_RENAME_BEGIN    FTP_COMMAND_BASE  +12           // ��ʼ������  
#define FTP_COMMAND_RENAME_END      FTP_COMMAND_BASE + 13           // ����������  
#define FTP_COMMAND_FILE_SIZE       FTP_COMMAND_BASE + 14           // ��ȡ�ļ���С  
#define FTP_COMMAND_DOWNLOAD_POS    FTP_COMMAND_BASE + 15           // �����ļ���ָ��λ�ÿ�ʼ  
#define FTP_COMMAND_DOWNLOAD_FILE   FTP_COMMAND_BASE + 16           // �����ļ�  
#define FTP_COMMAND_UPLOAD_FILE     FTP_COMMAND_BASE + 17           // �ϴ��ļ�  
#define FTP_COMMAND_APPEND_FILE     FTP_COMMAND_BASE + 18           // ׷�������ļ�   