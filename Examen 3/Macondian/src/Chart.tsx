///
/// Chart.tsx
///
import { LecturaSensor } from './Macondian';

interface Props {
  data: LecturaSensor[];
}

const Chart = ({ data }: Props) => {
  const hasData = data && data.length > 0;
  const maxVal = hasData ? Math.max(...data.map(d => d.macondos), 3.0) : 3.0;
  const showLabels = hasData && data.length <= 35;

  return (
    <div className="w-100 h-100 p-3 d-flex flex-column bg-dark text-light rounded overflow-hidden">
      {/* Encabezado y Leyenda fijas */}
      <div className="d-flex justify-content-between align-items-center mb-2 border-bottom border-secondary pb-2">
        <h6 className="text-warning mb-0 fw-bold">📈 Monitoreo Macondiano en Tiempo Real</h6>
        
        <div className="d-flex gap-3 small">
          <div className="d-flex align-items-center gap-1">
            <span className="d-inline-block rounded-circle bg-info" style={{ width: '10px', height: '10px' }}></span>
            <span className="text-light">Nivel Normal (&lt; 2.2)</span>
          </div>
          <div className="d-flex align-items-center gap-1">
            <span className="d-inline-block rounded-circle bg-warning" style={{ width: '10px', height: '10px' }}></span>
            <span className="text-light">Umbral Elevado (&ge; 2.2)</span>
          </div>
        </div>
      </div>

      {/* Área del Gráfico */}
      <div 
        className="flex-grow-1 d-flex align-items-end border-bottom border-secondary pb-2 px-1 position-relative" 
        style={{ 
          minHeight: 0, 
          gap: hasData && data.length > 60 ? '1px' : '2px', 
          overflow: 'hidden' 
        }}
      >
        {!hasData ? (
          /* Estado en espera con la cuadrícula vacía lista */
          <div className="position-absolute top-50 start-50 translate-middle text-center text-secondary">
            <p className="mb-0 fw-bold text-light">Gráfica lista. Esperando señal...</p>
            <small className="opacity-75">Presiona <b>Start</b> en la barra de herramientas para comenzar.</small>
          </div>
        ) : (
          /* Renderizado dinámico de barras */
          data.map((item, idx) => {
            const heightPct = Math.min((item.macondos / maxVal) * 100, 100);
            const isHigh = item.macondos >= 2.2;

            return (
              <div 
                key={idx} 
                className="d-flex flex-column align-items-center flex-fill h-100 justify-content-between" 
                style={{ minWidth: 0 }}
              >
                {showLabels ? (
                  <small style={{ fontSize: '0.6rem' }} className="text-warning fw-bold">
                    {item.macondos}
                  </small>
                ) : <div />}

                <div className="w-100 flex-grow-1 d-flex align-items-end my-1" style={{ minHeight: 0 }}>
                  <div 
                    className="w-100 rounded-top" 
                    style={{ 
                      height: `${heightPct}%`, 
                      transition: 'height 0.2s ease',
                      backgroundColor: isHigh ? '#ffc107' : '#0dcaf0' 
                    }} 
                    title={`Muestra #${idx + 1} | Batch ${item.batch} | Sensor ${item.sensorId}: ${item.macondos} Macondos`}
                  />
                </div>

                {showLabels ? (
                  <span className="text-light fw-semibold" style={{ fontSize: '0.6rem', letterSpacing: '0.5px' }}>
                    {item.sensorId}
                  </span>
                ) : <div />}
              </div>
            );
          })
        )}
      </div>

      {/* Pie del Gráfico fijo */}
      <div className="d-flex justify-content-between text-secondary small mt-2">
        <span>
          {hasData ? (
            <>
              <b>Total graficado: {data.length} sensores</b>
              {!showLabels && " (pasa el cursor sobre una barra para revisar valores)"}
            </>
          ) : (
            "(0 lecturas procesadas)"
          )}
        </span>
        <span>Escala máx: {maxVal.toFixed(2)} Macondos</span>
      </div>
    </div>
  );
};

export default Chart;