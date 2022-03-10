#define curr(P, i) P[i]
#define next(P, i) P[(i + 1)%P.size()]
long long area2(const vector<point> &P) {
  long long A = 0;
  for (int i = 0; i < P.size(); ++i)
    A += cross(curr(P, i), next(P, i));
  return A;
}