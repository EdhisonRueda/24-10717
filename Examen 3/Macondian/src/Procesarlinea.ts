
export interface SensorData {
  batch: number;
  sensorId: string;
  macondos: number;
}

export function procesarLineaCruda(linea: string, tolerancia: number = 0.08): SensorData | null {
  // Expresión regular para capturar: Batch, SensorID y el contenido entre corchetes [...]
  const regex = /^(\d+)\s+([A-Za-z0-9_]+)\s*\[\s*([\d\.\,\s]+)\s*\]$/;
  const match = linea.trim().match(regex);

  // Si no hace match (es una línea de encabezado o estado), se descarta
  if (!match) return null;

  const batch = parseInt(match[1], 10);
  const sensorId = match[2];
  
  // Convertir el texto de números separados por coma a un arreglo de float (equivalente a std::vector<double>)
  const rawValues: number[] = match[3]
    .split(',')
    .map(val => parseFloat(val.trim()))
    .filter(val => !isNaN(val));

  if (rawValues.length === 0) return null;

  // 1. Promedio preliminar para usar como referencia
  const sumaInicial = rawValues.reduce((acc, val) => acc + val, 0);
  const promedioInicial = sumaInicial / rawValues.length;

  // 2. Filtrar lecturas fuera del radio de tolerancia (outliers)
  const lecturasValidas = rawValues.filter(val => 
    Math.abs(val - promedioInicial) <= promedioInicial * tolerancia
  );

  // Si por alguna anomalía se filtraran todas, se usa el arreglo original
  const lecturasParaSintesis = lecturasValidas.length > 0 ? lecturasValidas : rawValues;

  // 3. Medida final de Macondos
  const sumaFinal = lecturasParaSintesis.reduce((acc, val) => acc + val, 0);
  const macondos = sumaFinal / lecturasParaSintesis.length;

  return {
    batch,
    sensorId,
    macondos: Number(macondos.toFixed(3))
  };
}