#ifndef SV_BLOCKLOGIC_H
#define SV_BLOCKLOGIC_H

#include <QDialog>

namespace Ui {
  class SvBlockLogic;
}

class SvBlockLogic : public QDialog
{
    Q_OBJECT
    
  public:
    explicit SvBlockLogic(QWidget *parent = 0);
    ~SvBlockLogic();
    
  private:
    Ui::SvBlockLogic *ui;
};

#endif // SV_BLOCKLOGIC_H
