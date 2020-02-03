#include <iostream>
#include <functional>
#include <QObject>
#include <wintoast/wintoastlib.h>


class MyHandler : public QObject, public WinToastLib::IWinToastHandler
{
    Q_OBJECT
public:
    explicit MyHandler(std::function<void()>&& activated = std::function<void()>(), std::function<void()>&& dismissed = std::function<void()>(), QObject *parent = nullptr) : QObject(parent), m_activated(activated), m_dismissed(dismissed) {}

    void toastActivated() const override
    {
        if (m_activated)
            m_activated();
        emit notifyActivated();
    }

    void toastActivated(int actionIndex) const override {}

    void toastDismissed(WinToastDismissalReason state) const override
    {
        if (state == WinToastDismissalReason::UserCanceled) {
            if (m_dismissed)
                m_dismissed();
            emit notifyDismissed();
        }
    }

    void toastFailed() const override {}

signals:
    void notifyActivated() const;
    void notifyDismissed() const;

private:
    std::function<void()> m_activated;
    std::function<void()> m_dismissed;

};


int main(int argc, char *argv[])
{
    std::cout << "Hello World!" << std::endl;


    if (!WinToastLib::WinToast::isCompatible()) {
        std::wcerr << L"Error, your system in not supported!" << std::endl;
        return 0;
    }

    MyHandler *h = new MyHandler([]() {
        std::cout << "activated" << std::endl;
    });

    WinToastLib::WinToastTemplate templ = WinToastLib::WinToastTemplate(WinToastLib::WinToastTemplate::Text02);
    templ.setTextField(L"Do you think this feature is cool?", WinToastLib::WinToastTemplate::FirstLine);
    templ.setTextField(L"Ofc,it is!", WinToastLib::WinToastTemplate::SecondLine);

    //std::vector<std::wstring> actions;
    //actions.push_back(L"Yes");
    //actions.push_back(L"No");
    //for (auto const &action : actions)
    //    templ.addAction(action);


    WinToastLib::WinToast::instance()->setAppName(L"testWinToast");
    const auto aumi = WinToastLib::WinToast::configureAUMI(L"cet-mipt", L"cet-studio", L"peaq", L"2.2.2");
    WinToastLib::WinToast::instance()->setAppUserModelId(aumi);
    WinToastLib::WinToast::WinToastError error = WinToastLib::WinToast::NoError;
    WinToastLib::WinToast::instance()->initialize(&error);
    if (error != WinToastLib::WinToast::NoError) {
        std::wcerr << L"Error, your system in not compatible!" << std::endl;
        return 0;
    }

    WinToastLib::WinToast::instance()->showToast(templ, h, &error);
    if (error != WinToastLib::WinToast::NoError) {
        std::wcout << L"Error: Could not launch your toast notification. Error: " << error << std::endl;
        return 0;
    }

    Sleep(30000);
    return 0;
}



#include "main.moc"
