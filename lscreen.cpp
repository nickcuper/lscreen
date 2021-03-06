#include <QtGui>
#include "lscreen.h"

 LScreen::LScreen()
 {
     screenshotLabel = new QLabel;
     screenshotLabel->setSizePolicy(QSizePolicy::Expanding,
                                    QSizePolicy::Expanding);
     screenshotLabel->setAlignment(Qt::AlignCenter);
     screenshotLabel->setMinimumSize(240, 160);

     createOptionsGroupBox();
     createButtonsLayout();

     mainLayout = new QVBoxLayout;
     mainLayout->addWidget(screenshotLabel);
     mainLayout->addWidget(optionsGroupBox);
     mainLayout->addLayout(buttonsLayout);
     setLayout(mainLayout);

     shootScreen();
     delaySpinBox->setValue(5);

     setWindowTitle(tr("LScreen"));
     resize(300, 200);
 }

 void LScreen::resizeEvent(QResizeEvent * /* event */)
 {
     QSize scaledSize = originalPixmap.size();
     scaledSize.scale(screenshotLabel->size(), Qt::KeepAspectRatio);
     if (!screenshotLabel->pixmap()
             || scaledSize != screenshotLabel->pixmap()->size())
         updateScreenshotLabel();
 }

 void LScreen::newScreenshot()
 {
     if (hideThisWindowCheckBox->isChecked())
         hide();
     newScreenshotButton->setDisabled(true);

     QTimer::singleShot(delaySpinBox->value() * 1000, this, SLOT(shootScreen()));
 }

 void LScreen::saveScreenshot()
 {
     QString format = "png";
     QString initialPath = QDir::currentPath() + tr("/untitled.") + format;

     QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                initialPath,
                                tr("%1 Files (*.%2);;All Files (*)")
                                .arg(format.toUpper())
                                .arg(format));
     if (!fileName.isEmpty())
         originalPixmap.save(fileName, format.toAscii());
 }

 // upload to server
 void LScreen::uploadScreenshot()
 {
    // QNetworkRequest request;
    //  request.setUrl(QUrl("http://qt.nokia.com"));
    //  request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");


 }

 void LScreen::shootScreen()
 {
     if (delaySpinBox->value() != 0)
         qApp->beep();
     originalPixmap = QPixmap(); // clear image for low memory situations
                                 // on embedded devices.
     originalPixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
     updateScreenshotLabel();

     newScreenshotButton->setDisabled(false);
     if (hideThisWindowCheckBox->isChecked())
         show();
 }

 void LScreen::updateCheckBox()
 {
     if (delaySpinBox->value() == 0) {
         hideThisWindowCheckBox->setDisabled(true);
         hideThisWindowCheckBox->setChecked(false);
     }
     else
         hideThisWindowCheckBox->setDisabled(false);
 }

 void LScreen::createOptionsGroupBox()
 {
     optionsGroupBox = new QGroupBox(tr("Options"));

     delaySpinBox = new QSpinBox;
     delaySpinBox->setSuffix(tr(" s"));
     delaySpinBox->setMaximum(60);
     connect(delaySpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCheckBox()));

     delaySpinBoxLabel = new QLabel(tr("Screenshot Delay:"));

     hideThisWindowCheckBox = new QCheckBox(tr("Hide This Window"));

     optionsGroupBoxLayout = new QGridLayout;
     optionsGroupBoxLayout->addWidget(delaySpinBoxLabel, 0, 0);
     optionsGroupBoxLayout->addWidget(delaySpinBox, 0, 1);
     optionsGroupBoxLayout->addWidget(hideThisWindowCheckBox, 1, 0, 1, 2);
     optionsGroupBox->setLayout(optionsGroupBoxLayout);
 }

 void LScreen::createButtonsLayout()
 {
     newScreenshotButton = createButton(tr("New"),
                                        this, SLOT(newScreenshot()));

     saveScreenshotButton = createButton(tr("Save"),
                                         this, SLOT(saveScreenshot()));

     uploadScreenshotButton = createButton(tr("Upload"),
                                         this, SLOT(uploadScreenshot()));

     quitScreenshotButton = createButton(tr("Quit"), this, SLOT(close()));

     buttonsLayout = new QHBoxLayout;
     buttonsLayout->addStretch();
     buttonsLayout->addWidget(newScreenshotButton);
     buttonsLayout->addWidget(saveScreenshotButton);
     buttonsLayout->addWidget(quitScreenshotButton);
     buttonsLayout->addWidget(uploadScreenshotButton);
 }

 QPushButton *LScreen::createButton(const QString &text, QWidget *receiver,
                                       const char *member)
 {
     QPushButton *button = new QPushButton(text);
     button->connect(button, SIGNAL(clicked()), receiver, member);
     return button;
 }

 void LScreen::updateScreenshotLabel()
 {
     screenshotLabel->setPixmap(originalPixmap.scaled(screenshotLabel->size(),
                                                      Qt::KeepAspectRatio,
                                                      Qt::SmoothTransformation));
 }
