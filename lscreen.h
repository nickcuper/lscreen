 #ifndef SCREENSHOT_H
 #define SCREENSHOT_H

 #include <QPixmap>
 #include <QWidget>
 #include <QtNetwork/QNetworkRequest>

 class QCheckBox;
 class QGridLayout;
 class QGroupBox;
 class QHBoxLayout;
 class QLabel;
 class QPushButton;
 class QSpinBox;
 class QVBoxLayout;
 class QNetworkRequest;

 class LScreen : public QWidget
 {
     Q_OBJECT

 public:
     LScreen();

 protected:
     void resizeEvent(QResizeEvent *event);

 private slots:
     void newScreenshot();
     void saveScreenshot();
     void shootScreen();
     void updateCheckBox();
     void uploadScreenshot();

 private:
     void createOptionsGroupBox();
     void createButtonsLayout();
     QPushButton *createButton(const QString &text, QWidget *receiver,
                               const char *member);
     void updateScreenshotLabel();

     QPixmap originalPixmap;

     QLabel *screenshotLabel;
     QGroupBox *optionsGroupBox;
     QSpinBox *delaySpinBox;
     QLabel *delaySpinBoxLabel;
     QCheckBox *hideThisWindowCheckBox;
     QPushButton *newScreenshotButton;
     QPushButton *saveScreenshotButton;
     QPushButton *quitScreenshotButton;
     QPushButton *uploadScreenshotButton;

     QVBoxLayout *mainLayout;
     QGridLayout *optionsGroupBoxLayout;
     QHBoxLayout *buttonsLayout;
 };

 #endif
