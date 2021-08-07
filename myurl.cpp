#include "myurl.h"

URL::URL(string url)
{
    m_url = url;

    m_Protocol = "";
    m_Hostname = "";
    m_RemoteFilePath = "";
    m_Port = 0;
}

string URL::getProtocol()
{
    return m_Protocol;
}

string URL::getHostname()
{
    return m_Hostname;
}

string URL::getFilePath()
{
    if(m_RemoteFilePath == "")
    {
        m_RemoteFilePath = "/";
        return m_RemoteFilePath;
    }
    return m_RemoteFilePath;
}

string URL::getRemoteDirectoryPath()
{
    string str = m_RemoteFilePath;
    if(m_RemoteFilePath == "")
    {
        m_RemoteFilePath = "/";
    }
    auto sign = str.find_last_of('.', str.length() - 1);
    int pos;
    if (sign != string::npos)
        pos = (int)sign;
    else
        pos = 1;

    string tmp_directorypath = str.substr(0, pos);
    auto sign2 = tmp_directorypath.find_last_of('/', tmp_directorypath.length() - 1);
    string directorypath = tmp_directorypath.substr(0, (int)sign2+1);
    //cout << directorypath << endl;
    return directorypath;
}

string URL::getDirectoryPath()
{
    if (m_RemoteFilePath == "")
    {
        m_RemoteFilePath = "/";
    }

    string str = m_RemoteFilePath;
    string directorypath;
    auto sign = str.find_last_of('.', str.length() - 1);  //查找'.'
    if(sign == string::npos)
    {
        directorypath = "../URL_FOLDER" + str;
        return directorypath;
    }
    else
    {
        string tmp_directorypath = "../URL_FOLDER" + str.substr(0, int(sign));

        auto sign2 = tmp_directorypath.find_last_of('/', tmp_directorypath.length() - 1);
        directorypath = tmp_directorypath.substr(0, int(sign2));
        return directorypath;
    }
    // string str = m_RemoteFilePath;
    // auto sign = str.find_last_of('.', str.length() - 1);
    // int pos;
    // if (sign != string::npos)
    //     pos = (int)sign;
    // else
    //     pos = 0;

    // string tmp_directorypath = "../URL_FOLDER" + str.substr(0, pos);
    // auto sign2 = tmp_directorypath.find_last_of('/', tmp_directorypath.length() - 1);
    // string directorypath = tmp_directorypath.substr(0, int(sign2));
    // //cout << directorypath << endl;
    // return directorypath;
}

string URL::getFileType()
{
    string str = m_RemoteFilePath;
    auto sign = str.find_last_of('.', str.length() - 1);
    int pos;
    if (sign != string::npos)
    {
        pos = (int)sign;
        string tmp_filetype = str.substr(pos + 1);

        auto pos2 = tmp_filetype.find_first_of('?', 0);
        string filetype;
        if(pos2 != string::npos)
        {
            filetype = tmp_filetype.substr(0, pos2);
        }
        else
        {
            filetype = tmp_filetype;
        }
        return filetype;
    }

    else
    {
        pos = 0;
        string filetype = "html";
        return filetype;
    }
}

string URL::getFile()
{
    string str = m_RemoteFilePath;
    if(m_RemoteFilePath == "")
    {
        m_RemoteFilePath = "/";
    }
    string filename;
    auto sign = str.find_last_of('.', str.length() - 1);
    int pos1, pos2;
    if (sign != string::npos)
    {
        pos1 = (int)sign;
        string tmp_str = str.substr(0, pos1);
        sign = tmp_str.find_last_of('/', str.length() - 1);
        pos2 = (int)sign;
        string tmp_filename = tmp_str.substr(pos2);
        filename = tmp_filename + getFileType();
    }
    else
    {
        filename = "/target." + getFileType();
    }
    return filename;
}

int URL::getPort()
{
    return m_Port;
}

//解析URL，从URL的各部分解析出协议，端口，域名以及远程文件路径
bool URL::getElements()
{
    // (([^:]+:)\/\/(([^:\/\?#]+)(:\d+)?))(\/[^?#]*)?(\?[^#]*)?(#.*)?
    // http(s)?://([\\w-]+\\.)+[\\w-]+(/[\\w- ./?%&=]*)?
    regex pattern("(\\w+)://([^/:]+)(?::(\\d*))?([^# ]*)");
    smatch result;

    bool signal = regex_match(m_url, result, pattern);
    if(signal)
    {
        cout << "The url is valid! " << endl;

        m_Protocol = result[1];
        m_Hostname = result[2];

        if(result[3]=="" && m_Protocol == "http")
            m_Port = 80;
        else if(result[3]=="" && m_Protocol == "https")
            m_Port = 443;
        else
            m_Port == stoi(result[3]);  //字符串转数字

        m_RemoteFilePath = result[4];

        return true;
    }
    else{
        cout << "The url is invalid! " << endl;
        return false;
    }
}