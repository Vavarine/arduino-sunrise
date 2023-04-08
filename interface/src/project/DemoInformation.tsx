import { FC } from "react";

import { Typography, Box, List, ListItem, ListItemText, Button } from "@mui/material";
import SaveIcon from "@mui/icons-material/Save";

import { SectionContent } from "../components";

import * as DemoApi from "./api";

const DemoInformation: FC = () => {
  const handleButtonClick = () => {
    DemoApi.updateAlarmsState({
      alarms: [
        {
          title: "Test Alarm",
          time: "2021-10-10T10:10:10",
          enabled: true,
          days: ["1", "2", "3", "4", "5", "6", "7"],
        },
        {
          title: "Test Alarm 2",
          time: "2021-10-10T10:10:10",
          enabled: true,
          days: ["1", "2", "6", "7"],
        },
      ],
    });
  };

  return (
    <SectionContent title="Demo Information" titleGutter>
      <Button
        startIcon={<SaveIcon />}
        variant="contained"
        color="primary"
        type="submit"
        onClick={handleButtonClick}
      >
        Save
      </Button>
      <Typography variant="body1" paragraph>
        This simple demo project allows you to control the built-in LED. It demonstrates how the
        esp8266-react framework may be extended for your own IoT project.
      </Typography>
      <Typography variant="body1" paragraph>
        It is recommended that you keep your project interface code under the project directory.
        This serves to isolate your project code from the from the rest of the user interface which
        should simplify merges should you wish to update your project with future framework changes.
      </Typography>
      <Typography variant="body1" paragraph>
        The demo project interface code is stored in the 'interface/src/project' directory:
      </Typography>
      <List>
        <ListItem>
          <ListItemText
            primary="ProjectMenu.tsx"
            secondary="You can add your project's screens to the side bar here."
          />
        </ListItem>
        <ListItem>
          <ListItemText
            primary="ProjectRouting.tsx"
            secondary="The routing which controls the screens of your project."
          />
        </ListItem>
        <ListItem>
          <ListItemText
            primary="DemoProject.tsx"
            secondary="This screen, with tabs and tab routing."
          />
        </ListItem>
        <ListItem>
          <ListItemText primary="DemoInformation.tsx" secondary="The demo information page." />
        </ListItem>
        <ListItem>
          <ListItemText
            primary="LightStateRestForm.tsx"
            secondary="A form which lets the user control the LED over a REST service."
          />
        </ListItem>
        <ListItem>
          <ListItemText
            primary="LightStateWebSocketController.tsx"
            secondary="A form which lets the user control and monitor the status of the LED over WebSockets."
          />
        </ListItem>
        <ListItem>
          <ListItemText
            primary="LightMqttSettingsForm.tsx"
            secondary="A form which lets the user change the MQTT settings for MQTT based control of the LED."
          />
        </ListItem>
      </List>
      <Box mt={2}>
        <Typography variant="body1">
          See the project <a href="https://github.com/rjwats/esp8266-react/">README</a> for a full
          description of the demo project.
        </Typography>
      </Box>
    </SectionContent>
  );
};

export default DemoInformation;
