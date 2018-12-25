#include <iostream>
#include <json/json.h>
#include <stdio.h>
#include <errno.h>
#include <fstream>
using namespace std;

void readJsonFile();
void readStrJson();
void readProStrJson();
void writeJsonFile();

int main(int argc, char const *argv[])
{
    //readJsonFile();
    //readStrJson();
    //readProStrJson();
    writeJsonFile();

    return 0;
}

void writeJsonFile()
{
    Json::Value root;
    Json::Value arrayObj;
    Json::Value item;
    for (int i=0; i<3; i++)
    {
        item["key"] = i;
        arrayObj.append(item);//数组形式
    }

    root["key1"] = "value1";
    root["key2"] = "value2";
    root["array"] = arrayObj;//子节点挂在根节点上
    //string out = root.toStyledString();
    //cout << out << std::endl;

    Json::FastWriter fw;//直接输出

    Json::StyledWriter sw;//缩进输出

    ofstream os;
    os.open("demo.json");
    os << sw.write(root);
    os.close();
}

void readProStrJson()
{
    string strValue = "{\"name\":\"json\",\"array\":[{\"cpp\":\"jsoncpp\"},{\"java\":\"jsoninjava\"},{\"php\":\"support\"}]}";
	/*
	//json内容如下：
	{
    "name": "json″,
    "array": [
        {
            "cpp": "jsoncpp"
        },
        {
            "java": "jsoninjava"
        },
        {
            "php": "support"
        }
    ]
	}
	*/
    Json::Reader reader;
    Json::Value root;

    reader.parse(strValue, root);

    cout << root["name"].asString() << endl;
    Json::Value tmp = root["array"];
    for(int i=0; i<tmp.size(); i++){
        if(!tmp[i].isMember("cpp")) continue;
        cout << tmp[i]["cpp"].asString() << endl;
    }

}

void readStrJson()
{
    //the same as string
    const char* str = "{\"praenomen\":\"Gaius\",\"nomen\":\"Julius\","
                        "\"cognomen\":\"Caezar\",\"born\":-100,\"died\":-44}";

    Json::Reader reader;
    Json::Value root;

    reader.parse(str, root);

    string praenomen = root["praenomen"].asString();
    int born = root["born"].asInt();

    cout << praenomen << " : " << born << endl;
}

void readJsonFile()
{
    Json::Value root;
    Json::Reader reader;

    ifstream ifs;
    ifs.open("example.json");
    if(!reader.parse(ifs, root)){
        perror("parse");
        return;
    }else{
        cout << root["encoding"].asString() << endl;
        cout << root["indent"]["length"].asInt() << endl;
        cout << root["indent"]["is_ok"].asBool() << endl;
    }

    if(root["tab"].isNull()){
        cout << "tab is null" << endl; 
    }else{
        cout << "tab isn`t null" << endl;
    }

    Json::Value plugObj = root["plug-ins"];
    for(int i=0; i<plugObj.size(); i++){
        if(!plugObj[i].isMember("c++")) continue;
        cout << plugObj[i]["c++"].asInt() << endl;
    }

    for(int i=0; i<root["ment"].size(); i++){
        cout << '\n' << endl;
        cout << root["ment"][i].asString() << endl;
    }

    ifs.close();
}
