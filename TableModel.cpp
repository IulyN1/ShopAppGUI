#include "TableModel.h"

QVariant MyTableModel::data(const QModelIndex& index, int role) const {
	if (role == Qt::DisplayRole) {
		Produs p = cos.get_all()[index.row()];
		if (index.column() == 0) {
			return QString::fromStdString(p.get_nume());
		}
		else if (index.column() == 1) {
			return QString::fromStdString(p.get_tip());
		}
		else if (index.column() == 2) {
			return QString::number(p.get_pret());
		}
		else if (index.column() == 3) {
			return QString::fromStdString(p.get_prod());
		}
	}
	return {};
}

QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			if (section == 0) {
				return QString("Name");
			}
			else if (section == 1) {
				return QString("Type");
			}
			else if (section == 2) {
				return QString("Price");
			}
			else if (section == 3) {
				return QString("Producer");
			}
		}
		else {
			return QString("%1").arg(section+1);
		}
	}
	return QVariant();
}

QVariant MyAdvancedTableModel::data(const QModelIndex& index, int role) const {
	if (role == Qt::DisplayRole) {
		Produs p = produse[index.row()];
		if (index.column() == 0) {
			return QString::fromStdString(p.get_nume());
		}
		else if (index.column() == 1) {
			return QString::fromStdString(p.get_tip());
		}
		else if (index.column() == 2) {
			return QString::number(p.get_pret());
		}
		else if (index.column() == 3) {
			return QString::fromStdString(p.get_prod());
		}
	}
	else if (role == Qt::UserRole) {
		Produs p = produse[index.row()];
		if (index.column() == 0) {
			return QString::number(p.get_id());
		}
	}
	else if (role == Qt::BackgroundRole) {
		for (int el : rows) {
			if (index.row() == el) {
				QBrush bg(Qt::yellow);
				return bg;
			}
		}	
	}
	return {};
}

QVariant MyAdvancedTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			if (section == 0) {
				return QString("Name");
			}
			else if (section == 1) {
				return QString("Type");
			}
			else if (section == 2) {
				return QString("Price");
			}
			else if (section == 3) {
				return QString("Producer");
			}
		}
		else {
			return QString("%1").arg(section + 1);
		}
	}
	return QVariant();
}

void MyAdvancedTableModel::setProducts(const vector<Produs>& produse) {
	this->produse = produse;
	QModelIndex topLeft = createIndex(0, 0);
	QModelIndex bottomRight = createIndex(rowCount(), columnCount());
	emit dataChanged(topLeft, bottomRight);
	emit layoutChanged();
}