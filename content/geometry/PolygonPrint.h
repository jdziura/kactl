/**
 * Author: Warsaw Eagles
 * Description: Nalezy przekierowac stdout do pliku i otworzyc go np. w przegladarce. Punkty (chyba) powinny byc doublami
 * \texttt{m} zwieksza obrazek, \texttt{d} zmniejsza rozmiar napisow/wierzchołkow.
 */
#pragma once

void polygon_print(vector<P> v, int r = 10) {
    int m = 350 / r, d = 50;
    auto ori = v;
    for (auto &p : v)
        p = P((p.x + r * 1.1) * m, (p.y + r * 1.1) * m);
    r = int(r * m * 2.5);
    printf("<svg height='%d' width='%d' xmlns='http://www.w3.org/2000/svg'><rect width='100%%' height='100%%' fill='white' />", r, r);
    int n = sz(v);
    rep(i,0,n) {
        printf("<line x1='%Lf' y1='%Lf' x2='%Lf' y2='%Lf' style='stroke:black' />", v[i].x, v[i].y, v[(i + 1) % n].x, v[(i + 1) % n].y);
        printf("<circle cx='%Lf' cy='%Lf' r='%f' fill='red' />", v[i].x, v[i].y, r / d / 10.0);
        printf("<text x='%Lf' y='%Lf' font-size='%d' fill='violet'>%d (%.1Lf, %.1Lf)</text>", v[i].x + 5, v[i].y - 5, r / d, i + 1, ori[i].x, ori[i].y);
    }
    printf("</svg>\n");
}
