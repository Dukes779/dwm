enum {MaxMon = 8};
static int nmasters[MaxMon];
static int initnm = 0;

static void
initnmaster(void) {
	int i;

	if(initnm)
		return;
	for(i = 0; i < MaxMon; i++)
		nmasters[i] = nmaster;
	initnm = 1;
}

/* static void */
/* incnmaster(const Arg *arg) { */
/* 	if(!arg || !selmon->lt[selmon->sellt]->arrange || selmon->num >= MaxMon) */
/* 		return; */
/* 	nmasters[selmon->num] += arg->i; */
/* 	if(nmasters[selmon->num] < 0) */
/* 		nmasters[selmon->num] = 0; */
/* 	arrange(); */
/* } */

static void
nbstack(Monitor *m) {
	int x, y, h, w, mh, nm;
	unsigned int i, n;
	Client *c;

	initnmaster();
	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	c = nexttiled(m->clients);
	nm = m->num < MaxMon ? nmasters[m->num] : nmaster;
	if(nm > n)
		nm = n;
	/* master */
	if(nm > 0) {
		mh = m->mfact * m->wh;
		w = m->ww / nm;
		if(w < bh)
			w = m->ww;
		x = m->wx;
		for(i = 0; i < nm; i++, c = nexttiled(c->next)) {
			resize(c, x, m->wy, ((i + 1 == nm) ? m->wx + m->ww - x : w) - 2 * c->bw,
			       (n == nm ? m->wh : mh) - 2 * c->bw, False);
			if(w != m->ww)
				x = c->x + WIDTH(c);
		}
		n -= nm;
	} else
		mh = 0;
	if(n == 0)
		return;
	/* tile stack */
	x = m->wx;
	y = m->wy + mh;
	w = m->ww / n;
	h = m->wh - mh;
	if(w < bh)
		w = m->ww;
	for(i = 0; c; c = nexttiled(c->next), i++) {
		resize(c, x, y, ((i + 1 == n) ? m->wx + m->ww - x : w) - 2 * c->bw,
		       h - 2 * c->bw, False);
		if(w != m->ww)
			x = c->x + WIDTH(c);
	}
}
