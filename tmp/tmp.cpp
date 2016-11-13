QList<QString> list;
list << "foo" << "bar" << "baz";

foreach( QString s, list )
	qDebug() << s;

QMap<QString, int> map;
map["foo"] = 42;
map["bar"] = 13;
map["baz"] = 9;
