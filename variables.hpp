namedColorList defaultColorList;
globalConfig currentConfig;

int currentColorCount = currentConfig.isHorizontalGradient ? COLUMNS : ROWS;

gradient currentGradient = {
    defaultColorList.aqua,
    defaultColorList.violet,
    false,
    false,
    currentColorCount
};

clockConfig currentClockConfig;
