open Belt;
open Type;
open Helper;

[@react.component]
let make = (~rowId: int, ~rotations: array(rotation)) => {
  let columnIds = Array.range(0, verticalCells - 1);
  let children =
    Array.map(
      columnIds,
      columnId => {
        let key =
          "moai-"
          ++ Int.toString(rowId)
          ++ "-"
          ++ Belt.Int.toString(columnId);
        let rotation = Option.getExn(rotations[columnId]);

        <Moai key rotation />;
      },
    );

  <div className="container"> {React.array(children)} </div>;
};
