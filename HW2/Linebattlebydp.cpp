#include <array>
#include <iostream>
#include <random>

namespace ada {

class Xoroshiro128 {
 public:
  using result_type = uint32_t;
  static constexpr result_type(min)() { return 0; }
  static constexpr result_type(max)() { return UINT32_MAX; }
  static inline result_type rotl(const result_type x, int k) {
    return (x << k) | (x >> (32 - k));
  }
  Xoroshiro128() : Xoroshiro128(1, 2, 3, 4) {}
  Xoroshiro128(result_type a, result_type b, result_type c, result_type d)
      : s{a, b, c, d} {}
  result_type operator()() {
    const result_type result = rotl(s[0] + s[3], 7) + s[0];
    const result_type t = s[1] << 9;
    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];
    s[2] ^= t;
    s[3] = rotl(s[3], 11);
    return result;
  }

 private:
  std::array<result_type, 4> s;
};

namespace {
int c_lead, c_team;
Xoroshiro128 rng;
}  // namespace

int Init() {
  int n;
  uint32_t s1, s2, s3, s4;
  std::cin >> n >> c_lead >> c_team >> s1 >> s2 >> s3 >> s4;
  rng = Xoroshiro128(s1, s2, s3, s4);
  return n;
}

int GetLeadership() { return uint64_t(rng()) * c_lead >> 32; }

int GetTeamValue() {
  int tmp = int(uint64_t(rng()) * c_team >> 32) + 1;
  return int(c_team / sqrt(tmp));
}

}  // namespace ada
#define NDEBUG
#define MAXN 2100000
#define MOD 1000000007
int n = ada::Init();
int leadership[MAXN], team_value[MAXN];
unsigned long long DP[MAXN] = {0};
unsigned long long DPsum[MAXN] = {0};
unsigned long long teamsum[MAXN] = {0};
unsigned long long abs(unsigned long long a, unsigned long long b){
    return (a > b)? (a - b) : (a + MOD - b);
}
int findk(int start, int end, unsigned long long rest){
  int k;
  int upbound = end;
  int lowbound = start + 1;
  
  while (upbound > lowbound){
      int mid = (upbound + lowbound) / 2;
      if (teamsum[mid] != teamsum[start]){
          unsigned long long target = abs(teamsum[mid], teamsum[start]);
          if (rest >= target){
              lowbound = mid + 1;
          }
          else{
              upbound = mid; 
          }
      }
  }
  
  return upbound;
}
void filltable(int n, int now, int leadership[], int team_value[]){
    for (int i = now; i >= 0; i--){
        if (i == n - 1){
          DP[i] = 1;
          DPsum[i + 1] = 0;
          DPsum[i] = 1;
        }
        else {
            int nowrest = leadership[i];
            int k = findk(i, n, nowrest);
            DP[i] = 0;
            DP[i] += (abs(DPsum[i + 1], DPsum[k]) % MOD);
            if (k < n)
                DP[i] += DP[k]; 
            else
                DP[i] += 1;
            
            DP[i] = DP[i] % MOD;
            DPsum[i] = (DPsum[i + 1] + DP[i]) % MOD;
        }
#ifndef NDEBUG
        printf("i %d DP %llu DPsum %llu\n", i, DP[i], DPsum[i]);
#endif
    }
    return;
}
int main(){
for (int i = 0; i < n; i++) leadership[i] = ada::GetLeadership();
for (int i = 0; i < n; i++) team_value[i] = ada::GetTeamValue();
#ifndef NDEBUG
	for (int i = 0; i < n; i++)
		printf("%d %d\n", leadership[i], team_value[i]);
#endif
    for (int i = 0; i < n; i++){
        if (i == 0)
            teamsum[i] = team_value[i];
        else
            teamsum[i] = (teamsum[i - 1] + team_value[i]);
    }
    teamsum[n] = teamsum[n - 1];
    filltable(n, n - 1, leadership, team_value);
    printf("%llu\n", DP[0]);
}