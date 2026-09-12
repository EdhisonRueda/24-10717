///
/// Macondian.tsx
///
import { procesarLineaCruda } from './Procesarlinea';
import { SubmitEvent, useEffect, useRef, useState } from 'react';

import Chart from "./Chart";
import CLI from "./CLI";
import Image from "./Image";
import List from "./List";
import Monitor from "./Monitor";
import ToolBar from "./ToolBar";

import 'bootstrap/dist/css/bootstrap.min.css';

const project = "ZenSheet™";
const artefact = "Macondian Simulator";
const version = "V-20260901";

const title = <h3>The Great {artefact}</h3>;
const product = <em><b>{artefact}</b> Interactive Computing Environment</em>;
const copyright = <>Copyright © <b>Lakebolt™ Research</b> 2024-2026</>;

const MONITOR_SIZE = 1024;

const tgmr = new Worker(new URL("./Macondian/tgmr-thx-1138.js", import.meta.url));

export interface LecturaSensor {
  batch: number;
  sensorId: string;
  macondos: number;
}

const Macondian = () => {
  const [structuredData, setStructuredData] = useState<LecturaSensor[]>([]);

  const imageContainerStyle: React.CSSProperties = {
    display: 'flex',
    flexDirection: 'column',
    alignItems: 'center',
    justifyContent: 'center',
    height: '100%',
    width: '100%',
    backgroundColor: '#121417',
    padding: '1.5rem',
    overflow: 'hidden'
  };

  const imageElementStyle: React.CSSProperties = {
    maxWidth: '100%',
    maxHeight: '85vh',
    objectFit: 'contain',
    borderRadius: '12px',
    boxShadow: '0 10px 30px rgba(0, 0, 0, 0.6)',
    border: '1px solid rgba(255, 255, 255, 0.1)'
  };

  const dividerStyle: React.CSSProperties = {
    width: '8px',
    cursor: 'col-resize',
    backgroundColor: '#2b3035',
    borderLeft: '1px solid #3f474e',
    borderRight: '1px solid #3f474e',
    display: 'flex',
    alignItems: 'center',
    justifyContent: 'center',
    userSelect: 'none'
  };

  const lastBatch = useRef<number | null>(null);
  const primerM = useRef(true);

  const command = useRef<HTMLInputElement>(null);

  const [rawLog, setRawLog] = useState<string[]>([]);
  const [seriesLog, setSeriesLog] = useState<string[]>([]);

  const addSeriesItem = (item: string) => {
    setSeriesLog(h => {
      return h.length < MONITOR_SIZE ? [...h, item] : [...h.slice(1), item];
    });
  };

  const addHistoryItem = (item: string) => {
    setRawLog(h => {
      const next = h.length < MONITOR_SIZE ? [...h, item] : [...h.slice(1), item];
      return next;
    });
  };

  const [ux, setUX] = useState(0);

  const uxColor = (mode: number) => {
    return mode === ux ? "Yellow" : "Gray";
  };

  const [error, setError] = useState<string>('');

  const [leftPct, setLeftPct] = useState(50);
  const splitRef = useRef<HTMLDivElement>(null);
  const dragging = useRef(false);

  useEffect(() => {
    tgmr.onmessage = (envelope: MessageEvent) => {
      const data = envelope.data;
      if (!data) {
        addHistoryItem(`ERROR: bad data in ${envelope}`);
        return;
      }
      
      addHistoryItem(data);

      if (primerM.current) {
        addSeriesItem(`Preparando procesamiento de señal...`);
        addSeriesItem(`:`);
        addSeriesItem(`Esperando señales macondianas`);
        addSeriesItem(`:`);
        primerM.current = false;
      }

      const resultado = procesarLineaCruda(data);

      if (resultado) {
        setStructuredData(prev => [...prev, resultado]);

        if (lastBatch.current !== resultado.batch) {
          addSeriesItem(`=== Batch ${resultado.batch} ===`);
          lastBatch.current = resultado.batch;
        }

        const lineaProcesada = ` ${resultado.batch}  ${resultado.sensorId}: ${resultado.macondos} Macondos`;
        addSeriesItem(lineaProcesada);
      }
    };
  }, []);

  const startDrag = (event: React.MouseEvent) => {
    event.preventDefault();
    dragging.current = true;
    document.body.style.userSelect = 'none';
    document.body.style.cursor = 'col-resize';
  };

  const send = (request: string) => {
    tgmr.postMessage(`${request}`);
  };

  const start = () => {
    send(".start");
  };

  const reset = () => {
    send(".reset");
    setTimeout(() => {
      setRawLog([]);
      setSeriesLog([]);
      setStructuredData([]);
      lastBatch.current = null; 
      primerM.current = true;
    }, 496);
  };

  const nop = () => {};

  const kvp = [
    { key: ".start", fun: start },
    { key: ".reset", fun: reset },
  ];

  const map = (key: string) => {
    for (let element of kvp) {
      if (key === element.key) {
        return element.fun;
      }
    }
    return nop;
  };

  const cliRequest = (event: SubmitEvent<HTMLFormElement>) => {
    event.preventDefault();
    if (command.current) {
      const request = command.current.value;
      command.current.value = "";
      map(request)();
    }
  };

  const rawView = (
    <div className="app-split" ref={splitRef}>
      <section className="app-pane" data-bs-theme="dark" style={{ flexGrow: leftPct }}>
        <Monitor title={"señal cruda"} log={rawLog} />
      </section>
      
      <div className="pane-divider" onMouseDown={startDrag} title="Drag to resize" style={dividerStyle}>
        <div style={{ width: '2px', height: '24px', backgroundColor: '#6c757d', borderRadius: '1px' }} />
      </div>
      
      <section className="app-pane" style={{ flexGrow: 100 - leftPct }}>
        <div style={imageContainerStyle}>
          <Image image={"MAC997.jpg"} style={imageElementStyle} />
          <small className="text-secondary mt-2">Diagrama de Simulación MAC-997</small>
        </div>
      </section>
    </div>
  );

  const testView = (
    <div className="app-split" ref={splitRef}>
      <section className="app-pane" data-bs-theme="dark" style={{ flexGrow: leftPct }}>
        <Monitor title={"señal cruda"} log={rawLog} />
      </section>
      <div className="pane-divider" onMouseDown={startDrag} title="Drag to resize" style={dividerStyle}>
        <div style={{ width: '2px', height: '24px', backgroundColor: '#6c757d', borderRadius: '1px' }} />
      </div>
      <section className="app-pane" style={{ flexGrow: 100 - leftPct }}>
        <Monitor title={"serie"} log={seriesLog} />
      </section>
    </div>
  );

  const chartView = (
    <div className="app-split" ref={splitRef}>
      <section className="app-pane" data-bs-theme="dark" style={{ flexGrow: leftPct }}>
        <Monitor title={"señal cruda"} log={rawLog} />
      </section>
      <div className="pane-divider" onMouseDown={startDrag} title="Drag to resize" style={dividerStyle}>
        <div style={{ width: '2px', height: '24px', backgroundColor: '#6c757d', borderRadius: '1px' }} />
      </div>
      <section className="app-pane" style={{ flexGrow: 100 - leftPct }}>
        <Chart data={structuredData} />
      </section>
    </div>
  );

  const imageView = (
    <div style={imageContainerStyle}>
      <div className="card bg-dark text-white border-secondary shadow-lg p-3 text-center" style={{ maxWidth: '900px', width: '100%' }}>
        <div className="card-header border-secondary d-flex justify-content-between align-items-center mb-3">
          <span className="badge bg-primary">MACONDIAN ART GALLERY</span>
          <small className="text-muted">Lakebolt Research Archives</small>
        </div>
        <div className="d-flex justify-content-center align-items-center" style={{ minHeight: '400px' }}>
          <Image image={Math.random() < 0.5 ? "ART042.jpg" : "ART067.png"} style={imageElementStyle} />
        </div>
      </div>
    </div>
  );

  const listView = (
    <div className="h-100 w-100 p-4 bg-dark text-light overflow-auto" data-bs-theme="dark" style={{ backgroundColor: '#121417' }}>
      <div className="card bg-dark text-light border-secondary shadow-lg p-3">
        <List />
      </div>
    </div>
  );

  const views = [ rawView, testView, chartView, imageView, listView ];

  return (
    <div className="app-shell">
      <header className="app-header">
        <>{title}</>
      </header>
      <ToolBar
        start={start}
        reset={reset}
        uxColor={uxColor}
        setUX={setUX}
        error={error}
      />
      <main className="app-main">
        { views[ux] }
      </main>
      <CLI req={cliRequest} ref={command} />
      <footer className="app-footer">
        <h6><b>{project}</b> Project: {product} {version} - {copyright} </h6>
      </footer>
    </div>
  );
};

export default Macondian;