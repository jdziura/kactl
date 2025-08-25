"""
 * Author: PurpleCrayon, Adam Soltan
 * Description: Simulated annealing. Neighbor function shouldn't change the answer by too much,
 * but it should be possible to get from any state to another in a small number of steps.
"""

def P(old, new, temp):
  if new < old:
    return 1.0
  return exp((old-new)/temp)

# tweak these:
temp_start = 10.0
temp_end = 0.1
def temperature(elapsed_frac):
  return temp_start * (temp_end / temp_start).pow(elapsed_frac)

s = random(state)
best = s
while elapsed_time() <= time_limit:
  t = temperature(elapsed_time()/time_limit)
  next = neighbor(s)
  if value(s) < value(best):
    best = s # important
  if P(value(s), value(next), t) >= random(0, 1):
    s = next

print(value(best))