#include "camera.h"
#include "ui_camera.h"
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>

Camera::Camera(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Camera)
{
    ui->setupUi(this);

    mCamera = new QCamera(this);
    mCameraViewfinder = new QCameraViewfinder(this);
    mCameraImageCapture = new QCameraImageCapture(mCamera, this);
    mLayout = new QVBoxLayout;
    mOptionsMenu = new QMenu("Options", this);
    mStartAction = new QAction("CameraStart", this);
    mStopAction = new QAction("CameraStop", this);
    mCapturarAction = new QAction("CameraCapturar", this);

    mCamera->setViewfinder(mCameraViewfinder);
    mLayout->addWidget(mCameraViewfinder);
    mLayout->setMargin(0);
    mOptionsMenu->addActions({mStartAction, mStopAction, mCapturarAction});

    ui->OptionsPushButton->setMenu(mOptionsMenu);
    ui->scrollArea->setLayout(mLayout);

    connect(mStartAction, &QAction::triggered, [&](){
        mCamera->start();
    });
    connect(mStopAction, &QAction::triggered, [&](){
        mCamera->stop();
    });
    connect(mCapturarAction, &QAction::triggered, [&](){
        //auto filename = QFileDialog::getSaveFileName(this, "CameraCapturar", "/", "Image Files (*.jpg;*.jpeg)");
        //if(filename.isEmpty())
        //{
        //    return;
        //}
        //mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
        //QImageEncoderSettings imageEncoderSettings;
        //imageEncoderSettings.setCodec("image/jpeg");
        //imageEncoderSettings.setResolution(1600, 1200);
        //mCameraImageCapture->setEncodingSettings(imageEncoderSettings);
        mCamera->setCaptureMode(QCamera::CaptureStillImage);
        mCamera->start();
        mCamera->searchAndLock();
        mCameraImageCapture->capture();
        mCamera->unlock();
    });
}

Camera::~Camera()
{
    delete ui;
}

