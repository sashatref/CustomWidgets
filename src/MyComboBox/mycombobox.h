#ifndef MY_COMBO_BOX_H
#define MY_COMBO_BOX_H

#include <QWidget>
#include <HelperLibrary/Widgets/extendedwidget.h>

#include "../export.h"

namespace Ui {
class MyComboBox;
}

class WIDGET_EXPORT MyComboBox : public ExtendedWidget
{
    Q_OBJECT
    Q_PROPERTY(bool removeButtonVisible READ getRemoveButtonVisible WRITE setRemoveButtonVisible)
    Q_PROPERTY(bool comboEditable READ getComboEditable WRITE setComboEditable)
    Q_PROPERTY(QSize buttonsSize READ getButtonsSize WRITE setButtonsSize RESET resetButtonsSize)
    Q_PROPERTY(QSizePolicy comboSizePolicy READ getComboSizePolicy WRITE setComboSizePolicy RESET resetSizePolicy)
public:
    MyComboBox(QWidget *parent = 0);
    ~MyComboBox();

    void initValues(const QStringList &_values);


    const QStringList &getValues() const;
    void setCurrentPreset(const QString &_preset);
    const QString &getCurrentPreset() const;

    void setRemoveButtonVisible(bool _isVisible);
    bool getRemoveButtonVisible() const;

    void setComboEditable(bool _isEditable);
    bool getComboEditable() const;

    void setButtonsSize(const QSize &_size);
    QSize getButtonsSize() const;
    void resetButtonsSize();

    void setComboSizePolicy(const QSizePolicy &_policy);
    QSizePolicy getComboSizePolicy() const;
    void resetSizePolicy();

Q_SIGNALS:
    void presetLoaded(const QString &_text);
    void presetRemoved(const QString &_text);
    void presetSaved(const QString &_text);

private slots:
    void on_saveButton_clicked();
    void on_removeButton_clicked();
    void comboBoxTextChanged(const QString &_text);

private:
    QStringList m_presets;
    QString     m_lastPreset;

    Ui::MyComboBox *ui;

    // ISaveWidget interface
public:
    virtual QVariant saveWidgetState() const override;
    virtual void loadWidgetState(const QVariant &_state) override;
    virtual void updateLanguage() override;
    virtual void updateStyle() override;

protected:
    virtual void initConnections() override;
};

#endif //MY_COMBO_BOX_H
