import { FC } from "react";

import { CssBaseline } from "@mui/material";
import { createTheme, responsiveFontSizes, ThemeProvider } from "@mui/material/styles";
import { indigo, blueGrey, orange, red, green, grey } from "@mui/material/colors";

import { RequiredChildrenProps } from "./utils";

const theme = responsiveFontSizes(
  createTheme({
    palette: {
      mode: "dark",
      text: {
        primary: "#fff",
        secondary: grey[500],
      },
      primary: {
        main: indigo[500],
      },
      secondary: {
        main: blueGrey[800],
      },
      info: {
        main: indigo[800],
      },
      warning: {
        main: orange[800],
      },
      error: {
        main: red[800],
      },
      success: {
        main: green[800],
      },
    },
  })
);

const CustomTheme: FC<RequiredChildrenProps> = ({ children }) => (
  <ThemeProvider theme={theme}>
    <CssBaseline />
    {children}
  </ThemeProvider>
);

export default CustomTheme;
