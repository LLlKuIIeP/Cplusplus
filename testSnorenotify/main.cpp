
#include <QApplication>
#include <libsnore/snore.h>
#include <libsnore/notification/notification.h>
//#include <libsnore/log.h>
using namespace Snore;
using namespace std;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //SnoreLog::setDebugLvl(3);
    //Set application name to distinguish settings for each app
    app.setApplicationName("send-notification-example");
    //Get the core
    auto& core = SnoreCore::instance();
    core.loadPlugins(SnorePlugin::Backend | SnorePlugin::SecondaryBackend);

    //All notifications have to have icon, so prebuild one
    Icon icon(QString(":/palette.png"));
    Application application(app.applicationName(), icon);
    

    //Also alert is mandatory, just choose the default one
    Alert alert(QString("Default"), icon);
    application.addAlert(alert);

    Notification n(application, alert, "First notification", "Hello world!", icon);
    core.registerApplication(application);
    // Optional: you can also set delivery date if you want to schedule notification
    //n.setDeliveryDate(QDateTime::currentDateTime().addSecs(5));

    core.broadcastNotification(n);

    //Connect slots if you need some action triggered by notification
//    app.connect(&core, &SnoreCore::actionInvoked, [&](Notification notification) { qDebug() << "Notification:" << notification.title() << "triggered!"; });
//    app.connect(&core, &SnoreCore::scheduledNotificationsChanged, [&]() {
//        for (auto notification : core.scheduledNotifications()) {
//            qDebug() << notification.id();
//        }
//    });
    return app.exec();
}
