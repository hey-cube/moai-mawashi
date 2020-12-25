open Belt
open Type

@react.component
let make = (~rotation: rotation) => {
  let src = "https://cdn.glitch.com/9b72fd1a-2e01-43db-b642-61eafd1cce17%2Fmoai.png?v=1602164795363"
  let alt = "moai"
  let style = ReactDOM.Style.make(~transform="rotate(" ++ (Float.toString(rotation) ++ "deg)"), ())

  <img src alt width="100" height="100" style />
}
