#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <sstream>


using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	   Mat frame;
	   char key = 0;
       //Declaramos una variable del tipo VideoCapture para poder acceder a la cámara
       VideoCapture cap("rtsp://biometria:1234$Bio@10.0.0.150/video.h264");
       //Instanciamos al Classificador
       CascadeClassifier detector;
//       if (!detector.load("haarcascade_frontalface_alt2.xml"))
//             cout << "No se puede abrir clasificador." << endl;
	   if(!detector.load("D:/opencv/build/share/OpenCV/haarcascades/haarcascade_eye_tree_eyeglasses.xml"))
			cout << "No se puede abrir clasificador para los ojos." << endl;

       //Revisamos si podemos acceder a la cámara por defecto de nuestro ordenador
       if (!cap.isOpened())
       {
             cout << "No se puede acceder a la Cámara." << endl;
       }
		namedWindow("Recortada");
	   resizeWindow("Recortada", 320, 280); 
       //Implementamos un bucle para ir obteniendo frame por frame e ir procesandolo independientemente
       while (key!=27)
       {
             Mat destino, gris, imagen;
             //Copiamos el frame de la secuencia de video y lo almacenamos en el objeto imagen
             cap.retrieve(imagen);
             //Convertimos a escala de Grises la imagen
             cvtColor(imagen, gris, CV_BGR2GRAY);
             //Ecualizamos la imagen para estandarizar el contraste
             equalizeHist(gris, destino);

             //Declaramos el vector donde se almacenarán las características de los ojos encontrados
             vector<Rect> rect;
             detector.detectMultiScale(destino, rect, 1.2, 3, 0, Size(60, 60));
			
             for (Rect rec : rect)
             {
                    rectangle(imagen,
                          Point(rec.x, rec.y),
                          Point(rec.x + rec.width, rec.y + rec.height),
                          CV_RGB(0, 0, 255), 1);
					imshow ( "Recortada" , gris(rec));

			 }
             //Mostramos uno a uno los frames con un rectángulo sobre los rostros detectados
             imshow("Deteccion de Ojos", imagen);
		
			 key=waitKey(20);	
		 }
	   //destroyWindow("Deteccion de Ojos");
	   
	   
	   waitKey ( 0 );
}
//#include "stdafx.h"
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include <string>
//#include <sstream>
//
//using namespace cv;
//using namespace std;
//
//int main(int argc, char* argv[])
//{
//	char key = 0;
//	int contador = 0;
//	//string fotoFilename = "0";
//	Mat frame, imagen;
//
//
//	cout << "Presionar 'Intro' para tomar foto" << std::endl;
//	cout << "Presionar 'Esc' para salir" << std::endl;
//
//	VideoCapture cam(0); //0 es la camara web, 1 otra camara
//
//	if(!cam.isOpened())
//	{
//		cout <<  "No se puede reproducir el video" << std::endl ;
//		return -1;
//	}
//	namedWindow("Camara");
//	
//	while (key!=27 && cam.grab()) 
//	{
//		cam.retrieve(frame);
//		imshow("Camara",frame);
//		   
//
//		if (key == 13) 
//		{
//			imagen = frame;
//			
//		//	imwrite(fotoFilename + ".jpg", frame);
//		//	contador++;
//		//	fotoFilename = static_cast<ostringstream*>(&(ostringstream() << contador))->str();
//			
//        }
//
//		key=waitKey(20);
//		
//	}
//	destroyWindow("Camara");
//	namedWindow( "Imagen", WINDOW_AUTOSIZE ); // Create a window for display.
//	imshow( "Imagen", imagen ); // Show our image inside it.
//	waitKey(0); 
//}
//	
//	float EYE_SX = 0.16f;
//	float EYE_SY = 0.26f;
//	float EYE_SW = 0.30f;
//	float EYE_SH = 0.28f;
//
//	Mat dest, gray;
//	//Mat imagen = imread("images.jpg");
//
//	CascadeClassifier detector, eyes_detector;
//
//	//if(!detector.load("haarcascade_frontalface_alt2.xml")) 
//	//	cout << "No se puede abrir clasificador." << endl;
//
//	if(!eyes_detector.load("haarcascade_eye_tree_eyeglasses.xml"))
//		cout << "No se puede abrir clasificador para los ojos." << endl;
//
//	cvtColor(imagen, gray, CV_BGR2GRAY);
//	equalizeHist(gray, dest);
//
//	vector<Rect> rect;
//	detector.detectMultiScale(dest, rect);
//
//	for(Rect rc : rect)
//	{
//		rectangle(imagen, 
//			Point(rc.x, rc.y), 
//			Point(rc.x + rc.width, rc.y + rc.height), 
//			CV_RGB(0,255,0), 2);
//	}
//
//	if(rect.size() > 0)
//	{
//		Mat face = dest(rect[0]).clone();
//		vector<Rect> leftEye, rightEye;
//
//		int leftX = cvRound(face.cols * EYE_SX);
//		int topY = cvRound(face.rows * EYE_SY);
//		int widthX = cvRound(face.cols * EYE_SW);
//		int heightY = cvRound(face.rows * EYE_SH);
//		int rightX = cvRound(face.cols * (1.0-EYE_SX-EYE_SW));
//
//		Mat topLeftOfFace = face(Rect(leftX, topY, widthX, heightY));
//		Mat topRightOfFace = face(Rect(rightX, topY, widthX, heightY));
//
//		eyes_detector.detectMultiScale(topLeftOfFace, leftEye);
//		eyes_detector.detectMultiScale(topRightOfFace, rightEye);
//
//		if((int)leftEye.size() > 0)
//		{
//			rectangle(imagen, 
//				Point(leftEye[0].x + leftX + rect[0].x, leftEye[0].y + topY + rect[0].y), 
//				Point(leftEye[0].width + widthX + rect[0].x - 5, leftEye[0].height + heightY + rect[0].y), 
//				CV_RGB(0,255,255), 2);
//		}
//
//		if((int)rightEye.size() > 0)
//		{
//			rectangle(imagen, 
//				Point(rightEye[0].x + rightX + leftX + rect[0].x, rightEye[0].y + topY + rect[0].y), 
//				Point(rightEye[0].width + widthX + rect[0].x + 5, rightEye[0].height + heightY + rect[0].y), 
//				CV_RGB(0,255,255), 2);
//		} 
//	}
//
//	imshow("Ojos", imagen);
//
//	waitKey(0);
//	return 1;
//}
//
//

