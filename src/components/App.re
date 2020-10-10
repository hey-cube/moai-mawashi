[@bs.send]
external getElementById: (Dom.document, string) => Dom.element =
  "getElementById";
[@bs.val] external document: Dom.document = "document";
[@bs.val] external alert: string => unit = "alert";
[@bs.get] external offsetTop: Dom.element => int = "offsetTop";
[@bs.get] external offsetLeft: Dom.element => int = "offsetLeft";

open Belt;
open Type;
open Helper;

[@react.component]
let make = () => {
  let (params, setParams) = React.useState(_ => initParams());
  let (mousePoint, setMousePoint) = React.useState(_ => ((0, 0): point));
  let (origin, setOrigin) = React.useState(_ => ((0, 0): point));
  let (intersection, setIntersection) = React.useState(_ => randomPoint());
  let (startTime, setStartTime) = React.useState(_ => 0.);

  let id = "field";

  React.useEffect1(
    () => {
      let field = getElementById(document, id);
      setOrigin(_ => (offsetLeft(field), offsetTop(field)));
      setStartTime(_ => Js.Date.now());
      None;
    },
    [||],
  );

  let rowIds = Array.range(0, horizontalCells - 1);
  let children =
    Array.map(
      rowIds,
      rowId => {
        let key = "row-" ++ Int.toString(rowId);
        let p = Array.getExn(params, rowId);
        let rotations = calculateRotations(intersection, mousePoint, p);

        <Row key rowId rotations />;
      },
    );

  let onMouseMove = (event: ReactEvent.Mouse.t) => {
    ReactEvent.Mouse.persist(event);
    let (originX, originY) = origin;
    setMousePoint(_ =>
      (
        ReactEvent.Mouse.clientX(event) - originX,
        ReactEvent.Mouse.clientY(event) - originY,
      )
    );
  };

  let onClick = (_: ReactEvent.Mouse.t) => {
    let (x, y) = mousePoint;
    let (interX, interY) = intersection;
    if (abs(x - interX) < 5 && abs(y - interY) < 5) {
      let time = Js.Date.now() -. startTime;
      alert(
        "Game clear!\nYour time is "
        ++ Float.toString(time)
        ++ "ms.\n(Press the OK button to initialize the game.)",
      );
      setParams(_ => initParams());
      setIntersection(_ => randomPoint());
      setStartTime(_ => Js.Date.now());
    };
  };

  <div id onClick onMouseMove> {React.array(children)} </div>;
};
