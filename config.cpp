#include "config.h"

Config::Config(QString filename)
{
    this->filename = filename;
    setting = new QSettings(this->filename, QSettings::IniFormat);
}

Config::~Config()
{
    delete setting;
    setting = nullptr;
}

//read
Config *Config::GetConfig()
{
    return new Config("config.ini");
}

int Config::screennum()
{
    return setting->value("screen/defaultscreen").toInt();
}

int Config::streamtype()
{
    return setting->value("camera/stream").toInt();
}

//write
void Config::setscreennum(int num)
{
    setting->setValue("screen/defaultscreen",num);
}

void Config::setstreamtype(int type)
{
    setting->setValue("camera/stream",type);
}



