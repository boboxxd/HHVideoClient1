#ifndef CONFIG_H
#define CONFIG_H
#include <QSettings>

class Config
{
public:
    static Config* GetConfig();
    int screennum();
    int streamtype();
    void setscreennum(int);
    void setstreamtype(int);
    ~Config();
private:
    Config(QString filename);

    QString filename;
    QSettings *setting;
    static Config *config;
};

#endif // CONFIG_H
