#include "StoreDashAdmin.h"
#include <QtWidgets/QApplication>

//namespace {
//
//	QString getToken()
//	{
//		QString body = "{ \"client_id\": \"BzL4Q8lag6ZKEjOcljqlOD5Dlwjaztcq\", \"client_secret\" : \"-53CuLQAslaOQzSOF9eWQv7C2w8svDfxI9jXRJltjKYDbgPC9dFwSW8GqUIilbyn\", \"audience\" : \"https://products-api.eu1.cluster.storeda.sh/\", \"grant_type\" : \"client_credentials\" }";
//		QByteArray d = body.toUtf8();
//
//		QNetworkAccessManager* manager = new QNetworkAccessManager();
//
//		QNetworkRequest request(QUrl{ "https://storedash-project.eu.auth0.com/oauth/token" });
//		request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
//
//		QNetworkReply* reply = manager->post(request, d);
//
//		QObject::connect(reply, &QNetworkReply::finished, [&]() {
//			if (reply->error() == QNetworkReply::NoError)
//			{
//				QString token = QJsonDocument::fromJson(reply->readAll()).object().value("access_token").toString();
//			}
//			else
//			{
//				QString err = reply->errorString();
//				qDebug() << err;
//			}
//			reply->deleteLater();
//			});
//	}
//
//	QByteArray getIds(const QString& token)
//	{
//		QNetworkRequest backendRequest(QUrl{ "https://products-api.eu1.cluster.storeda.sh/product/v1/layout" });
//		backendRequest.setRawHeader(QByteArray("Authorization"), QByteArray(("Bearer " + token.toStdString()).c_str()));
//		backendRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
//
//		QNetworkAccessManager* xmanager = new QNetworkAccessManager();
//		QNetworkReply* backendReply = xmanager->get(backendRequest);
//		QObject::connect(backendReply, &QNetworkReply::finished, [&]() {
//			if (backendReply->error() == QNetworkReply::NoError)
//			{
//				auto yo = backendReply->readAll();
//				int x = 4;
//			}
//			else
//			{
//				QString err = backendReply->errorString();
//				qDebug() << err;
//			}
//			backendReply->deleteLater();
//			});
//	}
//}


int main(int argc, char* argv[])
{
	//QString body = "{ \"client_id\": \"BzL4Q8lag6ZKEjOcljqlOD5Dlwjaztcq\", \"client_secret\" : \"-53CuLQAslaOQzSOF9eWQv7C2w8svDfxI9jXRJltjKYDbgPC9dFwSW8GqUIilbyn\", \"audience\" : \"https://products-api.eu1.cluster.storeda.sh/\", \"grant_type\" : \"client_credentials\" }";
	//QByteArray d = body.toUtf8();

	//QNetworkAccessManager* manager = new QNetworkAccessManager();

	//QNetworkRequest request(QUrl{ "https://storedash-project.eu.auth0.com/oauth/token" });
	//request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

	//QNetworkReply* reply = manager->post(request, d);

	//QObject::connect(reply, &QNetworkReply::finished, [&]() {
	//	if (reply->error() == QNetworkReply::NoError)
	//	{
	//		QString token = QJsonDocument::fromJson(reply->readAll()).object().value("access_token").toString();
	//		QNetworkRequest backendRequest(QUrl{ "https://products-api.eu1.cluster.storeda.sh/product/v1/layout" });
	//		backendRequest.setRawHeader(QByteArray("Authorization"), QByteArray(("Bearer " + token.toStdString()).c_str()));
	//		backendRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");

	//		QNetworkAccessManager* xmanager = new QNetworkAccessManager();
	//		QNetworkReply* backendReply = xmanager->get(backendRequest);
	//		QObject::connect(backendReply, &QNetworkReply::finished, [&]() {
	//			if (backendReply->error() == QNetworkReply::NoError)
	//			{
	//				auto yo = backendReply->readAll();
	//				int x = 4;
	//			}
	//			else
	//			{
	//				QString err = backendReply->errorString();
	//				qDebug() << err;
	//			}
	//			backendReply->deleteLater();
	//			});
	//	}
	//	else
	//	{
	//		QString err = reply->errorString();
	//		qDebug() << err;
	//	}
	//	reply->deleteLater();
	//	});

	QApplication a(argc, argv);
	StoreDashAdmin w;
	w.show();
	return a.exec();
}
