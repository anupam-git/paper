#ifndef INTERACTORS_INTERACTOR_H
#define INTERACTORS_INTERACTOR_H

#include <QObject>

class Interactor : public QObject {
  Q_OBJECT

 public:
  Interactor(QObject* parent = nullptr);
  virtual ~Interactor();

  virtual void execute() = 0;
};

#endif
