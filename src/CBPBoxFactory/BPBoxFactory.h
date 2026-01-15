#ifndef CBPBOXFACTORY_H
#define CBPBOXFACTORY_H

#include <QMap>
#include <QObject>

class COperationBox;
class CBPBoxFactoryInterface;

class CBPBoxFactory
{
    Q_DISABLE_COPY_MOVE(CBPBoxFactory)
  public:
    static CBPBoxFactory* getInstance();
    // used in CBPBoxManager and m_bpBoxBrowserList (left side menu )
    QList<COperationBox*> getListOfAllBPBoxes();
    QList<COperationBox*> findMatchingNodesWithStringQuery(const QString& query);
    COperationBox* createBPBoxInstance(const QString& boxName, const int& posX, const int& posY);

  private:
    explicit CBPBoxFactory();

  private:
    QMap<QString, CBPBoxFactoryInterface*> m_mapOfBPBoxToFactory;
};

#endif // CBPBOXFACTORY_H
