fn  ~(x, (a,b))     = 10
fn1 ~(x, (a,b))     = if x == 10 then a else x
fn2 ~(x,~(a,b))     = if x == 10 then a else x
fn3 ~(x, (a,b), c)  = if x == 10 then c else x

main = do
  print $ fn undefined          -- succeeds
  print $ fn1 undefined         --fails
  print $ fn1 (10, (20,30))     -- succeeds
  print $ fn1 (11, (20,30))     -- succeeds
  print $ fn1 (11, undefined)   -- fails
  print $ fn2 (11, undefined)   -- succeeds
  print $ fn2 (10, undefined)   -- fails
  -- A quirky thing
  fn3 (11, (20,30), undefined)  -- succeeds
  fn3 (11, undefined, 20)       -- fails
