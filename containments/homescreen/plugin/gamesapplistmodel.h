/*
 *   Copyright (C) 2014 Antonis Tsiapaliokas <antonis.tsiapaliokas@kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2,
 *   or (at your option) any later version, as published by the Free
 *   Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef GAMEAPPLISTMODEL_H
#define GAMEAPPLISTMODEL_H

// Qt
#include <QObject>
#include <QAbstractListModel>
#include <QList>

class QString;

struct GapplicationData {
    QString name;
    QString icon;
    QString storageId;
    QString entryPath;
    QString desktopPath;
    bool startupNotify = true;
};

class GamesAppListModel : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QStringList appOrder READ appOrder WRITE setAppOrder NOTIFY appOrderChanged)

public:
    GamesAppListModel(QObject *parent = nullptr);
    ~GamesAppListModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    void moveRow(const QModelIndex &sourceParent, int sourceRow, const QModelIndex &destinationParent, int destinationChild);

    int count() { return m_applicationList.count(); }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    enum Roles {
        ApplicationNameRole = Qt::UserRole + 1,
        ApplicationIconRole,
        ApplicationStorageIdRole,
        ApplicationEntryPathRole,
        ApplicationDesktopRole,
        ApplicationStartupNotifyRole,
        ApplicationOriginalRowRole
    };

    QStringList appOrder() const;
    void setAppOrder(const QStringList &order);

    Q_INVOKABLE void moveItem(int row, int order);

    Q_INVOKABLE void runApplication(const QString &storageId);

    Q_INVOKABLE void loadApplications();

public Q_SLOTS:
     void sycocaDbChanged(const QStringList &change);

Q_SIGNALS:
    void countChanged();
    void appOrderChanged();

private:
    QList<GapplicationData> m_applicationList;

    QStringList m_appOrder;
    QHash<QString, int> m_appPositions;
};

#endif // GAMESAPPLISTMODEL_H 