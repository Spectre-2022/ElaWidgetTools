#ifndef ELACOMBOBOXSTYLE_H
#define ELACOMBOBOXSTYLE_H

#include <QProxyStyle>

#include "Def.h"
class ElaComboBoxStyle : public QProxyStyle
{
    Q_OBJECT
    Q_PROPERTY_CREATE(qreal, ExpandIconRotate)
    Q_PROPERTY_CREATE(qreal, ExpandMarkWidth)
public:
    explicit ElaComboBoxStyle(QStyle* style = nullptr);
    ~ElaComboBoxStyle() override;
    void drawPrimitive(PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex* option, QPainter* painter, const QWidget* widget = nullptr) const override;

    QRect subControlRect(ComplexControl cc, const QStyleOptionComplex* opt, SubControl sc, const QWidget* widget) const override;
    QSize sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& size, const QWidget* widget) const override;

private:
    ElaThemeType::ThemeMode _themeMode;
    int _shadowBorderWidth{0};  //@TODO:因为其会影响使用代理时的显示效果，故暂时修改为0；
};

#endif // ELACOMBOBOXSTYLE_H
