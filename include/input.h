#pragma once

void processInputEvent();
//wird von SDL aufgerufen, wenn Taste gedrückt wurde
//bekommt Info darüber, welche Taste gedrückt wurde
//ruft zugehörige Aktion über switch caseauf
            // z.B. bei Pfeiltaste -> rufe snakeSetDir auf
            // im Menü bei Settings -> rufe menuNavigate auf