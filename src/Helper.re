open Belt;
open Type;

let verticalCells = 8;
let horizontalCells = 5;
let moaiSize = 100;
let vertical = verticalCells * moaiSize;
let horizontal = horizontalCells * moaiSize;

let pythagorean = (a: float, b: float) => sqrt(a ** 2. +. b ** 2.);

let diagonal = pythagorean(Int.toFloat(vertical), Int.toFloat(horizontal));

let randomPoint = (): point => {
  Random.self_init();

  (Random.int(vertical + 1), Random.int(horizontal + 1));
};

let initParams = (): array(array(param)) => {
  Random.self_init();

  let randomFloat = (min: float, max: float) => {
    Random.float(max -. min) +. min;
  };

  let randomParam = (): param => {
    // 絶対値1以下と1以上が同じくらい生成されて欲しい
    let slope =
      Random.bool() ? randomFloat(-1., 1.) : randomFloat(-10., 10.);
    let cycle = randomFloat(30., diagonal);

    (slope, cycle);
  };

  let makeRow = (n: int) => {
    Array.makeBy(n, _ => randomParam());
  };

  let params = Array.makeBy(horizontalCells - 1, _ => makeRow(verticalCells));
  let exRow =
    makeRow(verticalCells - 1)
    ->Array.concat([|(randomFloat(-1., 1.), diagonal +. 30.)|]) // 1つだけ cycle が diagonal より大きいモアイを作る
    ->Array.shuffle;
  Array.concat(params, [|exRow|])->Array.shuffle;
};

let calculateRotations =
    (intersection: point, mousePoint: point, params: array(param))
    : array(rotation) => {
  let (xInt, yInt) = mousePoint;
  let (x, y) = (Int.toFloat(xInt), Int.toFloat(yInt));
  let (pInt, qInt) = intersection;
  let (p, q) = (Int.toFloat(pInt), Int.toFloat(qInt));

  Array.map(
    params,
    param => {
      let (a, m) = param;
      let b = q -. a *. p;
      let d = (a *. x -. y +. b) /. pythagorean(a, -1.);
      let r = d *. 360. /. m;
      r;
    },
  );
};
