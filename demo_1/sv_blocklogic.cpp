#include "sv_blocklogic.h"
#include "ui_sv_blocklogic.h"

SvBlockLogic::SvBlockLogic(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SvBlockLogic)
{
  ui->setupUi(this);
}

SvBlockLogic::~SvBlockLogic()
{
  delete ui;
}
