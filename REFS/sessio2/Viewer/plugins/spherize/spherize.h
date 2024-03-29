#ifndef _SPHERIZE_H
#define _SPHERIZE_H

#include "basicplugin.h"
#include <QGLShader>
#include <QGLShaderProgram>


class spherize : public QObject, public BasicPlugin
 {
     Q_OBJECT
     Q_INTERFACES(BasicPlugin)

 public:
    void onPluginLoad();
    void preFrame();
    void postFrame();
    
 private:
    QGLShaderProgram* program;
    QGLShader* shader; 
 };
 
 #endif
