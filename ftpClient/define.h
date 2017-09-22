#pragma once





#define ArraySize(ptr)		(sizeof(ptr) / sizeof(ptr[0]))
#define B2b(returnValue)	(returnValue) == TRUE ? true : false

#define FTP_API                     int
#define FTP_DEFAULT_PORT            21                              //FTP默认端口号  
#define FTP_DEFAULT_BUFFER          1024*4                          //FTP下载缓冲默认大小  
#define FTP_DEFAULT_PATH            "/mnt/dvs/"                     //FTP默认保存路径  

#define FTP_COMMAND_BASE            1000  
#define FTP_COMMAND_END             FTP_COMMAND_BASE + 30  
#define FTP_COMMAND_USERNAME        FTP_COMMAND_BASE + 1            //用户名  
#define FTP_COMMAND_PASSWORD        FTP_COMMAND_BASE + 2            //密码  
#define FTP_COMMAND_QUIT            FTP_COMMAND_BASE + 3            //退出  
#define FTP_COMMAND_CURRENT_PATH    FTP_COMMAND_BASE + 4            // 获取文件路径  
#define FTP_COMMAND_TYPE_MODE       FTP_COMMAND_BASE + 5            // 改变传输模式  
#define FTP_COMMAND_PSAV_MODE       FTP_COMMAND_BASE + 6            // 被动端口模式  
#define FTP_COMMAND_DIR             FTP_COMMAND_BASE + 7            // 获取文件列表  
#define FTP_COMMAND_CHANGE_DIRECTORY FTP_COMMAND_BASE + 8           // 改变路径  
#define FTP_COMMAND_DELETE_FILE     FTP_COMMAND_BASE + 9            // 删除文件  
#define FTP_COMMAND_DELETE_DIRECTORY FTP_COMMAND_BASE + 10          // 删除目录/文件夹  
#define FTP_COMMAND_CREATE_DIRECTORY FTP_COMMAND_BASE + 11          // 创建目录/文件夹  
#define FTP_COMMAND_RENAME_BEGIN    FTP_COMMAND_BASE  +12           // 开始重命名  
#define FTP_COMMAND_RENAME_END      FTP_COMMAND_BASE + 13           // 重命名结束  
#define FTP_COMMAND_FILE_SIZE       FTP_COMMAND_BASE + 14           // 获取文件大小  
#define FTP_COMMAND_DOWNLOAD_POS    FTP_COMMAND_BASE + 15           // 下载文件从指定位置开始  
#define FTP_COMMAND_DOWNLOAD_FILE   FTP_COMMAND_BASE + 16           // 下载文件  
#define FTP_COMMAND_UPLOAD_FILE     FTP_COMMAND_BASE + 17           // 上传文件  
#define FTP_COMMAND_APPEND_FILE     FTP_COMMAND_BASE + 18           // 追加上载文件   