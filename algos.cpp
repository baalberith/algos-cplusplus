#include <iostream>
#include <cmath>
using namespace std;

struct data {
  int klucz;
};

struct node {
  data dane;
  int nastepny;
};

const int n = 25, mn = 1, mx = n;
data t[n + 1];

void bubble_sort_1(data t[], int n) {
  bool posortowane = false;
  for (int j = n - 1; j >= 1 && !posortowane; j--) {
    posortowane = true;
    for (int i = 1; i <= j; i++)
      if (t[i].klucz > t[i + 1].klucz) {
        swap(t[i], t[i + 1]);
        posortowane = false;
      }
  }
}

void bubble_sort_2(data t[], int n) {
  int poczatek = 1, 
  koniec = n - 1, pozycja;
  do {
    pozycja = 0;
    for (int i = poczatek; i <= koniec; i++) 
      if (t[i].klucz > t[i + 1].klucz) {
        swap(t[i], t[i + 1]);
        if (pozycja == 0)
          if (i > 1)
            poczatek = i - 1;
          else
            poczatek = 1;
        pozycja = i;
      }
    koniec = pozycja - 1;
  } while (pozycja != 0);
}

void bidirectional_bubble_sort(data t[], int n) {
  int poczatek = 1, 
  koniec = n - 1, pozycja;
  do {
    pozycja = 0;
    for (int i = poczatek; i <= koniec; i++)
      if (t[i].klucz > t[i + 1].klucz) {
        swap(t[i], t[i + 1]);
        pozycja = i;
      }
    koniec = pozycja - 1;
    if (pozycja != 0) {
      pozycja = 0;
      for (int i = koniec; i >= poczatek; i--)
        if (t[i].klucz > t[i + 1].klucz) {
          swap(t[i], t[i + 1]);
          pozycja = i;
        }
      poczatek = pozycja + 1;
    }
  } while (pozycja != 0);
}

int comb_gap(int odstep) {
  if (odstep > 1) {
    odstep *= 10 / double(13);
    if (odstep == 9 || odstep == 10) 
      odstep = 11;
  }
  return odstep;
}

void comb_sort(data t[], int n) {
  bool posortowane = false;
  int odstep = n;
  while (odstep > 1 || !posortowane) {
    posortowane = true;
    odstep = comb_gap(odstep);
    for (int i = 1; i + odstep <= n; i++)
      if (t[i].klucz > t[i + odstep].klucz) {
        swap(t[i], t[i + odstep]);
        posortowane = false;
      }
  }
}

void selection_sort(data t[], int n) {
  for (int j = 1; j <= n - 1; j++) {
    int minimum = j;
    for (int i = j + 1; i <= n; i++) 
      if (t[i].klucz < t[minimum].klucz)
        minimum = i;
    swap(t[j], t[minimum]);
  } 
}

void insertion_sort(data t[], int n) {
  for (int j = n - 1; j >= 1; j--) {
    data schowek = t[j];
    int i = j + 1;
    while (i <= n && t[i].klucz < schowek.klucz) {
      t[i - 1] = t[i];
      i++;
    }
    t[i - 1] = schowek;
  }
}

int recursive_binary_search(data t[], int n, int szukana, int poczatek, int koniec) {
  if (koniec - poczatek > 1) {
    int srodek = (poczatek + koniec) / 2;
    if (szukana <= t[srodek].klucz)
      return recursive_binary_search(t, n, szukana, poczatek, srodek);
    else
      return recursive_binary_search(t, n, szukana, srodek, koniec);
  } 
  else 
    return poczatek;
} 

int iterative_binary_search(data t[], int n, int szukana) {
  int poczatek = 0, 
  koniec = n + 1;
  while (koniec - poczatek > 1) {
    int srodek = (poczatek + koniec) / 2;
    if (szukana <= t[srodek].klucz)
      koniec = srodek;
    else
      poczatek = srodek;
  }
  return poczatek;
}

void binary_insertion_sort(data t[], int n) {
  for (int j = n - 1; j >= 1; j--) {
    data schowek = t[j];
    int pozycja = recursive_binary_search(t, n, schowek.klucz, j, n + 1);
    // int pozycja = iterative_binary_search(t, n, schowek.klucz);
    for (int i = j + 1; i <= pozycja; i++)
      t[i - 1] = t[i];
    t[pozycja] = schowek;
  }
}

int shell_gap(int n) {
  int odstep;
  for (odstep = 1; odstep < n; odstep = 3 * odstep + 1);
    odstep /= 9; 
  if (odstep == 0) odstep++;
  return odstep;
}

void shell_sort(data t[], int n) {
  int odstep = shell_gap(n);
  while (odstep > 0) {
    for (int j = n - odstep; j >= 1; j--) {
      data schowek = t[j];
      int i = j + odstep;
      while (i <= n && t[i].klucz < schowek.klucz) {
        t[i - odstep] = t[i];
        i += odstep;
      }
      t[i - odstep] = schowek;
    }
    odstep /= 3;
  }
}

void merge_1(data t[], int poczatek, int srodek, int koniec) {
  int ilosc = koniec - poczatek + 1;
  data schowek[ilosc + 1]; 
  int lewa = poczatek, 
  prawa = srodek + 1;
  for (int i = 1; i <= ilosc; i++)
    schowek[i] = prawa > koniec || lewa <= srodek && t[lewa].klucz < t[prawa].klucz ? t[lewa++] : t[prawa++];
  for (int i = 1; i <= ilosc; i++) 
    t[poczatek + i - 1] = schowek[i];
}

void merge_2(data t[], int poczatek, int srodek, int koniec) {
  int ilosc = srodek - poczatek + 1;
  data schowek[ilosc + 1];
  int lewa = 1, 
  prawa = srodek + 1, 
  pozycja = poczatek;
  for (int i = 1; i <= ilosc; i++)
    schowek[i] = t[poczatek + i - 1];
  while (lewa <= ilosc && prawa <= koniec) 
    t[pozycja++] = schowek[lewa].klucz < t[prawa].klucz ? schowek[lewa++] : t[prawa++];
  while (lewa <= ilosc)
    t[pozycja++] = schowek[lewa++];
}

void merge_insitu(data t[], int poczatek, int srodek, int koniec) {
  if (poczatek < srodek) {   
    // zamiana 2) t[poczatek..srodek] z 1) t[1..srodek-poczatek+1]
    for (int i = poczatek; i <= srodek; i++) 
      swap(t[i - poczatek + 1], t[i]);
    int lewy = 1, // 1)
    prawy = srodek + 1, // 3)
    scalony = poczatek - 1; // 2)
    // 2) t[poczatek..scalony] - scalone podciągi 
    // 1) t[1..lewy-1] i 3) t[srodek+1..prawy-1]
    while (lewy <= srodek - poczatek + 1 && prawy <= koniec) {
      scalony++;
      if (t[lewy].klucz <= t[prawy].klucz) 
        swap(t[lewy++], t[scalony]);
      else 
        swap(t[prawy++], t[scalony]);
    }
    while (lewy <= srodek - poczatek + 1) {
      scalony++;
      swap(t[lewy++], t[scalony]);
    }
  }
  else if (poczatek == srodek) {
    data schowek = t[poczatek];
    int i = poczatek + 1;
    while (i <= koniec && t[i].klucz < schowek.klucz) {
      t[i - 1] = t[i];
      i++;
    }
    t[i - 1] = schowek;
  }
}

void recursive_merge_sort(data t[], int poczatek, int koniec) {
  if (poczatek < koniec) {
    int srodek = (poczatek + koniec) / 2;
    recursive_merge_sort(t, poczatek, srodek);
    recursive_merge_sort(t, srodek + 1, koniec);
    merge_1(t, poczatek, srodek, koniec);
    //merge_2(t, poczatek, srodek, koniec);
  }
}

void iterative_merge_sort(data t[], int n) {
  for (int odstep = 1; odstep < n; odstep *= 2) {
    int i;
    for (i = 1; i + 2 * odstep - 1 <= n; i += 2 * odstep) 
      merge_1(t, i, i + odstep - 1, i + 2 * odstep - 1);
      //merge_2(t, i, i + odstep - 1, i + 2 * odstep - 1);
    if (i + odstep <= n)
      merge_1(t, i, i + odstep - 1, n);
      //merge_2(t, i, i + odstep - 1, n);
  }
}

void mergesort_insitu(data t[], int poczatek, int koniec) {
  if (poczatek < koniec) {
    int srodek = (poczatek + koniec) / 2,
    ssrodek = (poczatek + srodek) / 2;
    mergesort_insitu(t, srodek + 1, koniec);
    while (poczatek < srodek) {
      mergesort_insitu(t, ssrodek + 1, srodek);
      merge_insitu(t, ssrodek + 1, srodek, koniec);
      srodek = ssrodek;
      ssrodek = (poczatek + srodek) / 2;
    }
    merge_insitu(t, poczatek, poczatek, koniec);
  }
}

void mergesort_natural(data t[], int n) {
  int lewy = 1, srodek = 1, prawy = 0;
  while (prawy - lewy + 1 < n) {
    prawy = 0;
    while (prawy + 1 <= n) {
      lewy = prawy + 1;
      srodek = lewy;
      while (srodek < n && t[srodek].klucz <= t[srodek + 1].klucz)
        srodek++;
      prawy = srodek + 1;
      while (prawy < n && t[prawy].klucz <= t[prawy + 1].klucz)
        prawy++;
      if (prawy <= n)
        merge_1(t, lewy, srodek, prawy);
        //merge_2(t, lewy, srodek, prawy);
    }
  }
}

void heapify_recursive(data t[], int wierzcholek, int ilosc) {
  int lewy = 2 * wierzcholek, 
  prawy = lewy + 1, 
  maksimum = wierzcholek;
  if (lewy <= ilosc && t[lewy].klucz > t[wierzcholek].klucz)
    maksimum = lewy;
  if (prawy <= ilosc && t[prawy].klucz > t[maksimum].klucz)
    maksimum = prawy;
  if (maksimum != wierzcholek) {
    swap(t[wierzcholek], t[maksimum]);
    heapify_recursive(t, maksimum, ilosc);
  }
}

void heapify_iterative(data t[], int ilosc) {
  int wierzcholek = 1, 
  lewy = 2,
  prawy = 3, maksimum;
  while (prawy <= ilosc && max(t[lewy].klucz, t[prawy].klucz) > t[wierzcholek].klucz || lewy <= ilosc && t[lewy].klucz > t[wierzcholek].klucz) {
    if (prawy <= ilosc && t[prawy].klucz > t[lewy].klucz)
      maksimum = prawy;
    else
      maksimum = lewy;
    swap(t[wierzcholek], t[maksimum]);
    wierzcholek = maksimum; 
    lewy = 2 * wierzcholek;
    prawy = lewy + 1;
  }
}

void build_heap_1(data t[], int n) {
  for (int i = n / 2; i >= 1; i--) 
    heapify_recursive(t, i, n);
}

void build_heap_2(data t[], int n) {
  for (int i = 2; i <= n; i++) {
    data schowek = t[i];
    int wierzcholek = i, 
    poprzednik = wierzcholek / 2;
    while (poprzednik >= 1 && t[poprzednik].klucz < schowek.klucz) {
      t[wierzcholek] = t[poprzednik];
      wierzcholek = poprzednik; 
      poprzednik = wierzcholek / 2;
    }
    t[wierzcholek] = schowek;
  }
}

void heap_sort(data t[], int n) {
  build_heap_1(t, n);
  //build_heap_2(t, n);
  for (int i = n; i >= 2; i--) { 
    swap(t[1], t[i]);
    heapify_recursive(t, 1, i - 1);
    //heapify_iterative(t, i - 1);
  }
}

void heapify_down(data t[], int n, int wierzcholek) {
  heapify_recursive(t, wierzcholek, n);
}

void heapify_up(data t[], int wierzcholek) {
  int rodzic = wierzcholek / 2;
  while (wierzcholek > 1 && t[rodzic].klucz < t[wierzcholek].klucz) {
    swap(t[rodzic], t[wierzcholek]);
    wierzcholek = rodzic;
    rodzic = wierzcholek / 2;
  }
}

void heap_insert(data t[], int n, int pozycja, data nowy) {
  if (nowy.klucz != t[pozycja].klucz) {
    data schowek = t[pozycja];
    t[pozycja] = nowy;
    if (nowy.klucz < schowek.klucz)
      heapify_down(t, n, pozycja);
    else
      heapify_up(t, pozycja);
  } 
}

int hoare_partition(data t[], int lewy, int prawy) {
  data piwot = t[prawy];
  int poczatek = lewy - 1,
  koniec = prawy;
  while (true) {
    do {
      poczatek++;
    } while (t[poczatek].klucz < piwot.klucz);
    do {
      koniec--;
    } while (t[koniec].klucz > piwot.klucz);
    if (poczatek < koniec)
      swap(t[poczatek], t[koniec]);
    else {
      swap(t[poczatek], t[prawy]);
      return poczatek;
    }
  }
}

int lomuto_partition(data t[], int lewy, int prawy) {
  data piwot = t[prawy];
  int indeks = lewy - 1;
  for (int i = lewy; i < prawy; i++)
    if (t[i].klucz <= piwot.klucz) {
      indeks++;
      swap(t[indeks], t[i]);
    }
  swap(t[indeks + 1], t[prawy]);
  return indeks + 1;
}

void quick_sort(data t[], int lewy, int prawy) {
  if (lewy < prawy) {
    int podzial = hoare_partition(t, lewy, prawy);
    //int podzial = lomuto_partition(t, lewy, prawy);
    quick_sort(t, lewy, podzial - 1);
    quick_sort(t, podzial + 1, prawy);
  }
}

data quick_select(data t[], int lewy, int prawy, int ktory) {
  if (lewy == prawy)
    return t[lewy];
  int podzial = hoare_partition(t, lewy, prawy),
  //int podzial = lomuto_partition(t, lewy, prawy),
  ilosc = podzial - lewy + 1;
  if (ktory < ilosc)
    return quick_select(t, lewy, podzial - 1, ktory);
  else if (ktory > ilosc)
    return quick_select(t, podzial + 1, prawy, ktory - ilosc);
  else
    return t[podzial];
}

void median_of_medians(data t[], int lewy, int prawy, int ktory) {
  int ilosc = prawy - lewy + 1;
  if (ilosc <= 5) {
    insertion_sort(t + lewy - 1, ilosc);
    //quick_select(t, lewy, prawy, ktory);
    swap(t[lewy], t[lewy + ktory - 1]);
  }
  else {
    int ilegrup = ilosc / 5;
    for (int grupa = 0; grupa < ilegrup; grupa++) {
      int przesuniecie = grupa * 5;
      insertion_sort(t + lewy + przesuniecie - 1, 5);
      //quick_select(t, lewy + przesuniecie, lewy + przesuniecie + 4, 3);
      swap(t[lewy + grupa], t[lewy + przesuniecie + 2]);
    }
    int ostatni = lewy + ilegrup - 1;
    median_of_medians(t, lewy, ostatni, (ilegrup + 2) / 2);
    int podzial = hoare_partition(t, lewy, prawy),
    //int podzial = lomuto_partition(t, lewy, prawy),
    ile = podzial - lewy + 1;
    if (ktory < ile)
      median_of_medians(t, lewy, podzial - 1, ktory);
    else if (ktory > ile) {
      median_of_medians(t, podzial + 1, prawy, ktory - ile);
      swap(t[lewy], t[podzial + 1]);
    }
    else
      swap(t[lewy], t[podzial]);
  }
}

void distribution_sort(data t[], int n) {
  data liczby[10][n];
  int jednosci[10] = {},
  dziesiatki[10] = {},
  pozycja = 1;
  for (int i = 1; i <= n; i++) {
    int j = t[i].klucz % 10;
    liczby[j][jednosci[j]++] = t[i];
  }
  for (int j = 0; j < 10; j++)
    for (int i = 0; i < jednosci[j]; i++) 
      t[pozycja++] = liczby[j][i];
  for (int i = 1; i <= n; i++) {
    int d = t[i].klucz / 10;
    liczby[d][dziesiatki[d]++] = t[i];
  }
  pozycja = 1;
  for (int d = 0; d < 10; d++)
    for (int i = 0; i < dziesiatki[d]; i++) 
      t[pozycja++] = liczby[d][i];
}

void bucket_sort(data t[], int n, int minimum, int maksimum) {
  node lista[n + 1];
  int naglowek[n + 1],
  szerokosc = (maksimum - minimum + 1) / n,
  pozycja = 1;
  for (int i = 0; i <= n; i++)
    naglowek[i] = 0;
  for (int i = 1; i <= n; i++) {
    data schowek = t[i];
    int kubelek = (schowek.klucz - minimum + 1) / szerokosc,
    poprzedni = 0,
    biezacy = naglowek[kubelek];
    lista[i].dane = schowek;
    lista[i].nastepny = 0;
    while (biezacy > 0 && lista[biezacy].dane.klucz < schowek.klucz) {
      poprzedni = biezacy;
      biezacy = lista[biezacy].nastepny;
    }
    if (poprzedni != 0) {
      lista[poprzedni].nastepny = i;
      if (biezacy != 0)
        lista[i].nastepny = biezacy;
    }
    else {
      naglowek[kubelek] = i;
      lista[i].nastepny = biezacy;
    }
  }
  for (int i = 0; i <= n; i++) {
    int indeks = naglowek[i];
    while (indeks != 0) {
      t[pozycja++] = lista[indeks].dane;
      indeks = lista[indeks].nastepny;
    }
  }
}

void counting_sort(data t[], int n, int minimum, int maksimum) {
  data schowek[n + 1];
  int ilosc = maksimum - minimum + 1,
  licznik[ilosc + 1];
  for (int i = minimum; i <= maksimum; i++)
    licznik[i - minimum + 1] = 0;
  for (int i = 1; i <= n; i++)
    licznik[t[i].klucz - minimum + 1]++;
  for (int i = minimum + 1; i <= maksimum; i++)
    licznik[i - minimum + 1] += licznik[i - minimum];
  for (int i = n; i >= 1; i--)
    schowek[licznik[t[i].klucz - minimum + 1]--] = t[i];
  for (int i = 1; i <= n; i++)
    t[i] = schowek[i];
}

void radix_sorting(data t1[], data t2[], int maska) {
  int licznik[2] = {};
  for (int i = 1; i <= n; i++) 
    licznik[(t1[i].klucz & maska) > 0]++;
  licznik[1] += licznik[0];
  for (int i = n; i >= 1; i--)
    t2[licznik[(t1[i].klucz & maska) > 0]--] = t1[i];
}

void radix_sort(data t[], int n, int maksimum) {
  data schowek[n + 1];
  int maska = 1;
  while (maska <= maksimum) {
    radix_sorting(t, schowek, maska);
    maska <<= 1;
    radix_sorting(schowek, t, maska);
    maska <<= 1;
  }
}

pair<data, data> min_max_search(data t[], int n) {
  if (n > 2) {
    int minimum = t[1].klucz < t[2].klucz ? 1 : 2,
    maksimum = t[1].klucz > t[2].klucz ? 1 : 2;
    for (int i = 3; i < n - (n % 2); i += 2) 
      if (t[i].klucz < t[i + 1].klucz) {
        if (t[i].klucz < t[minimum].klucz)
          minimum = i;
        if (t[i + 1].klucz > t[maksimum].klucz)
          maksimum = i + 1;
      }
      else {
        if (t[i].klucz > t[maksimum].klucz)
          maksimum = i;
        if (t[i + 1].klucz < t[minimum].klucz)
          minimum = i + 1;
      }
    if (n % 2 == 1) {
      if (t[n].klucz < t[minimum].klucz)
        minimum = n;
      if (t[n].klucz > t[maksimum].klucz)
        maksimum = n;
    }
    return make_pair(t[minimum], t[maksimum]);
  }
  else
    return make_pair(t[1].klucz < t[2].klucz ? t[1] : t[2], t[1].klucz > t[2].klucz ? t[1] : t[2]);
}

pair<int, int> min_max_recursive(data t[], int poczatek, int koniec) {
  if (poczatek == koniec) 
    return make_pair(poczatek, koniec);
  else
    if (poczatek + 1 == koniec)
      if (t[poczatek].klucz < t[koniec].klucz)
        return make_pair(poczatek, koniec);
      else
        return make_pair(koniec, poczatek);
    else {
      int srodek = (poczatek + koniec) / 2,
      minimum, maksimum;
      pair<int, int> lewy = min_max_recursive(t, poczatek, srodek),
      prawy = min_max_recursive(t, srodek + 1, koniec);
      if (t[lewy.first].klucz < t[prawy.first].klucz)
        minimum = lewy.first;
      else
        minimum = prawy.first;
      if (t[lewy.second].klucz > t[prawy.second].klucz)
        maksimum = lewy.second;
      else
        maksimum = prawy.second;
      return make_pair(minimum, maksimum);
    }
}

pair<bool, data> lider_search(data t[], int n) {
  int lider = 1,
  ilosc = 1;
  for (int i = 2; i <= n; i++) 
    if (ilosc == 0) {
      lider = i;
      ilosc = 1;
    }
    else {
      if (t[i].klucz == t[lider].klucz)
        ilosc++;
      else 
        ilosc--;
    }
  if (ilosc > 0) {
    ilosc = 0;
    for (int i = 1; i <= n; i++)
      if (t[i].klucz == t[lider].klucz)
        ilosc++;
  }
  return make_pair(ilosc > n / 2, t[lider]);
} 

double fast_power_1(double liczba, int wykladnik) {
  double wynik = 1;
  while (wykladnik) {
    if (wykladnik % 2 == 1)
      wynik *= liczba;
    liczba *= liczba;
    wykladnik /= 2;
  }
  return wynik;
}

double sqr(double liczba) {
  return liczba * liczba;
}

double fast_power_2(double liczba, int wykladnik) {
  if (wykladnik == 1)
    return liczba;
  double tmp = fast_power_2(liczba, wykladnik / 2);
  if (wykladnik % 2 == 1)
    return sqr(tmp) * liczba;
  else
    return sqr(tmp);
}

pair<int, pair<int, int> > euclidean_extended(int n, int m) {
  int a = n, aa = m,
  x = 1, xx = 0,
  y = 0, yy = 1;
  while (aa != 0) {
    int q = a / aa,
    tmp = aa;
    aa = a - q * aa;
    a = tmp;
    tmp = xx;
    xx = x - q * xx;
    x = tmp;
    tmp = yy;
    yy = y - q * yy;
    y = tmp;
  }
  return make_pair(a, make_pair(x, y));
}

int gcd(int n, int m) {
  if (m == 0)
    return n;
  return gcd(m, n % m);
}

pair<int, int> fraction_add(pair<int, int> a, pair<int, int> b) {
  int r = gcd(a.second, b.second),
  t = a.first * (b.second / r) + b.first * (a.second / r),
  s = gcd(t, r);
  return make_pair(t / s, (a.second / r) * (b.second / s));
}

pair<int, int> fraction_multiply(pair<int, int> a, pair<int, int> b) {
  int r = gcd(a.first, b.second),
  s = gcd(a.second, b.first);
  return make_pair((a.first / r) * (b.first / s), (a.second / s) * (b.second / r));
}

void eratosthenes_sieve(int m) {
  int n = (m - 1) / 2;
  bool t[n + 1];
  for (int i = 1; i <= n; i++)
    t[i] = true;
  int i = 1,
  p = 3,
  q = 4;
  while (q <= n) {
    if (t[i++] == 1) 
      for (int j = q; j <= n; j += p)
        t[j] = false;
    p += 2;
    q += 2 * p - 2;
  }
  cout << 2 << " ";
  for (int i = 1; i <= n; i++)
    if (t[i] == true)
      cout << 2 * i + 1 << " ";
  cout << endl;
}

double newton_raphson(double liczba, double epsilon) {
  double przyblizenie = liczba / 2,
  pierwiastek = (przyblizenie + liczba / przyblizenie) / 2;
  while (abs(przyblizenie - pierwiastek) > epsilon) {
    przyblizenie = pierwiastek;
    pierwiastek = (przyblizenie + liczba / przyblizenie) / 2;
  }
  return pierwiastek;
}

int fibonacci_number(int n) {
  if (n <= 2) 
    return 1;
  int fib1 = 1,
  fib2 = 1;
  n -= 2;
  while (n--) {
    fib2 = fib1 + fib2;
    fib1 = fib2 - fib1;
  }
  return fib2;
}

int main() {
  srand(time(0)); 
  for (int i = 1; i <= n; i++) 
    cout << (t[i].klucz = 1 + rand() % n) << " ";
  cout << endl;
  int ktory = 1 + rand() % n;
  median_of_medians(t, 1, n, ktory);
  cout << ktory << " " << t[1].klucz << endl;
  quick_sort(t, 1, n);
  for (int i = 1; i < ktory; i++) 
    cout << t[i].klucz << " ";
  cout << "| " << t[ktory].klucz << " |" << " ";
  for (int i = ktory + 1; i <= n; i++) 
    cout << t[i].klucz << " ";
  cout << endl;
}
