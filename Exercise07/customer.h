#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>
#include <QStringList>
#include <QObject>

class Customer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ getTitle WRITE setTitle)
    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(QStringList address READ getAddress WRITE setAddress)
    Q_PROPERTY(QString postCode READ getPostCode WRITE setPostCode)
    Q_PROPERTY(QString code READ getCode WRITE setCode)
    Q_PROPERTY(double balance READ getBalance WRITE setBalance)

public:
    Customer();
    Customer(QString t, QString n, QStringList a, QString pc, QString c, double amt);

    QString getTitle() const;
    void setTitle(QString t);

    QString getName() const;
    void setName(QString n);

    QStringList getAddress() const;
    void setAddress(QStringList a);

    QString getPostCode() const;
    void setPostCode(QString pc);

    QString getCode() const;
    void setCode(QString c);

    double getBalance() const;
    void setBalance(double amt);

    QString toString() const;

private:
    QString m_title;
    QString m_name;
    QStringList m_address;
    QString m_postCode;
    QString m_code;
    double m_balance;
};

#endif // CUSTOMER_H
