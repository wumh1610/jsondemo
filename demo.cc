#include <iostream>
#include <json/json.h>
using namespace std;

int main(int argc, char const *argv[])
{
    Json::Value root;
    Json::Value arrayObj;
    Json::Value item;
    for (int i=0; i<3; i++)
    {
        item["key"] = i;
        arrayObj.append(item);
    }

    root["key1"] = "“value1″";
    root["key2"] = "“value2″";
    root["array"] = arrayObj;
    string out = root.toStyledString();
    cout << out << std::endl;

    return 0;
}
