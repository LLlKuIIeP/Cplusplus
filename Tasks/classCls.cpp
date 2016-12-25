struct pubCls {
	pubCls(int c, double d, int i);
	char c;
	double d;
	int i;
};

pubCls *p;

char& get_c(Cls &cls) {
	p = (pubCls*)(&cls);
	//std::cout << p->c << "\n";
	return (p->c);
}

double& get_d(Cls &cls) {
	p = (pubCls*)(&cls);
	return (p->d);
}

int& get_i(Cls &cls) {
	p = (pubCls*)(&cls);
	return (p->i);
}
