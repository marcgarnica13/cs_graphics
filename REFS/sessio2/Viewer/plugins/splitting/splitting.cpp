#include "splitting.h"
#include <QFileDialog>
 
void Splitting::onPluginLoad()
{
	// VS
      QString vs_src = "uniform float radius; void main() {	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; 	gl_FrontColor  = gl_Color; 	gl_TexCoord[0] = (1.0/radius)*(gl_Vertex.xyzw+gl_Vertex.zxyw); }";
    	vs = new QGLShader(QGLShader::Vertex, this);
    	vs->compileSourceCode(vs_src);

	// FS
  //
  QString fs_src = 
    "uniform sampler2D tex1;"
    "uniform sampler2D tex2;"
    "uniform sampler2D noise;"
    "void main()"
    "{"
    "	float r = texture2D(noise, gl_TexCoord[0].st).r;"
    "	"
    "	gl_FragColor = mix(	texture2D(tex1, gl_TexCoord[0].st),"
    "						texture2D(tex2, gl_TexCoord[0].st),"
    "						r);"
    "}";

  fs = new QGLShader(QGLShader::Fragment, this);
  fs->compileSourceCode(fs_src);

	// Program  
  program = new QGLShaderProgram(this);
  program->addShader(vs);
	program->addShader(fs);
	program->link();

	// Load Texture 1
	glActiveTexture(GL_TEXTURE0);
	QString filename = QFileDialog::getOpenFileName(0, "Open Image", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");	
	QImage img0(filename);	
	QImage im0 = QGLWidget::convertToGLFormat(img0);
	glGenTextures( 1, &textureId0);
	glBindTexture(GL_TEXTURE_2D, textureId0);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glBindTexture(GL_TEXTURE_2D, 0);

	// Load Texture 2
	glActiveTexture(GL_TEXTURE1);
	QString filename2 = QFileDialog::getOpenFileName(0, "Open Image 2", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");	
	QImage img1(filename2);	
	QImage im1 = QGLWidget::convertToGLFormat(img1);
	glGenTextures( 1, &textureId1);
	glBindTexture(GL_TEXTURE_2D, textureId1);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im1.width(), im1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im1.bits());
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glBindTexture(GL_TEXTURE_2D, 0);


	// Load Texture 3
	glActiveTexture(GL_TEXTURE2);
	QString filename3 = QFileDialog::getOpenFileName(0, "Open Image 3", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");	
	QImage img2(filename3);	
	QImage im2 = QGLWidget::convertToGLFormat(img2);
	glGenTextures( 1, &textureId2);
	glBindTexture(GL_TEXTURE_2D, textureId2);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im2.width(), im2.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im2.bits());
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Splitting::preFrame() 
{
  // bind shader and define uniforms
  program->bind();
  program->setUniformValue("tex1", 0);  // texture unit del primer sampler 
  program->setUniformValue("tex2", 1);  // texture unit del segon  sampler 
  program->setUniformValue("noise", 2);  // texture unit del segon  sampler 
  program->setUniformValue("radius", float(scene()->boundingBox().radius()));  // radi d'una esfera que engloba l'escena
  // bind textures
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureId0);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, textureId1);
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, textureId2);
}

void Splitting::postFrame() 
{
  // unbind shader
  program->release();
  // unbind textures
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, 0);
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, 0);
}

Q_EXPORT_PLUGIN2(splitting, Splitting)   // plugin name, plugin class
