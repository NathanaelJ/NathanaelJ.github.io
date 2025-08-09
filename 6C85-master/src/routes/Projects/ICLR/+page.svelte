<svelte:head>
  <title>Rocketry | N Jenkins</title>
</svelte:head>

<main class="site-main">
  <div class="wrapper">
      <h1>Imperial College London Rocketry</h1>
      <h2>The Altitude Record Team at Imperial College London Rocketry<br/><br/></h2>
      
      <p>The Altitude Record Team (ART) is a project within <a href="https://imperialrocketry.com" target="_blank" rel="noreferrer noopener">Imperial College London Rocketry (ICLR)</a> which exists to break <a href="https://ukra.ork.uk" target="_blank" rel="noreferrer noopener">United Kingdom Rocketry Association (UKRA)</a> altitude records. The team formed in 2019, with its first two launches in early 2021. Three further launches took place over the 2021-22 academic year, including our first record-breaking flight. As of 2024, the team is continuing to work towards more altitude records using advanced rocket technology.<br/><br/>I led the aerodynamics and simulations sub-team, using computational methods to model and optimise the behaviour of our rocket. We used packages including <a href="https://openrocket.info" target="_blank" rel="noreferrer noopener">OpenRocket</a>, <a href="https://www.plm.automation.siemens.com/global/en/products/simcenter/STAR-CCM.html" target="_blank" rel="noreferrer noopener">StarCCM+</a>, and <a href="https://engineering.esteco.com/modefrontier/" target="_blank" rel="noreferrer noopener">ESTECO modeFrontier</a>.<br/><br/></p>
      
      <hr width="50%" size="1px" color="#555" z-index="1">
      <h3>ASTRA</h3>
      <p>This is a family of test-bed rockets used to verify systems in preparation for record-breaking flights. Three successful flights took place during my tenure, testing progressively more advanced systems. The family has continued to be used for increasingly complex test flights.<br/><br/></p>
      
      <div class="image-container">
          <img src="ICLRResources/ASTRA.png" alt="ASTRA Family">
      </div>

      <hr width="50%" size="1px" color="#555" z-index="1">
      <h3>APEX</h3>
      <p>The APEX family of rockets are designed to break UKRA altitude records for various motor classes. Rocket motors are classified based on their total impulse (essentially a measure of the 'amount of push' they provide). The ICLR Altitude Record Team now holds the record for an I-Class rocket as of 2024.<br/><br/></p>
      <p><b>APEX I</b> reached 9333ft (3845m) with a single motor, breaking the previous record of 9199ft. It travelled at supersonic speeds (Mach 1.55) thanks to its highly optimised design.<br/><br/></p>
      
      <div class="image-container">
          <img src="ICLRResources/APEXI.png" alt="APEX I">
      </div>

      <hr width="50%" size="1px" color="#555" z-index="1">
      <h3>modeFrontier</h3>
      <p><a href="https://engineering.esteco.com/modefrontier/" target="_blank" rel="noreferrer noopener">ESTECO</a> kindly provided ICL Rocketry with licenses to use their powerful multidisciplinary optimisation (MDO) software, modeFrontier. This 'plugs in' to many engineering modelling packages and can be used to optimise complex designs in much shorter timeframes, and with much greater control over simulations, than our previous methods. The team successfully used it to break the I-Class record with APEX-I. Documents on our use of the tool can be found below:
      <br/><a href="ICLRResources/oR_mF/oRmFIntegration.html">openRocket-modeFrontier Integration</a>
      <br/><a href="ICLRResources/oR_mF/NSGA_HYBRID.html">NSGA-HYBRID Performance Evaluation</a><br/><br/></p>

      <hr width="50%" size="1px" color="#555" z-index="1">
      <h3>Flights</h3>
      <div class="video-container">
          <p><a href="ICLRResources/ASTRA.mp4">ASTRA Mk.I, 11.04.2021 (EARS event)</a></p>
          <h2>First ART flight<br/>Successful launch and (partial) recovery of a rocket<br/>Use and validation of in-house avionics systems<br/>Verification of OpenRocket predictions for low-mach flight<br/>Successful implementation of in-house lugless launch system<br/>Validation of ASTRA's structure<br/><br/></h2>
          <p><br/><a href="ICLRResources/ASTRA2.mp4">ASTRA Mk.II, 13.06.2021 (EARS event)</a></p>
          <h2>Successful launch and recovery of a rocket<br/>Use and validation of revised in-house avionics systems<br/>Data collection for verification of ASTOS simulations<br/>Lugless launch system improvements noted (caused slight wobble)<br/>Validation of improved recovery system<br/><br/></h2>
          <p><br/><a href="ICLRResources/APEX.mp4">APEX I, 03.07.2022 (Supported by SARA)</a></p>
          <h2>I-Class altitude record<br/>Successful use of improved launcher system<br/>Launch system fin strike identified and issues investigated<br/>Further validation of tracking and recovery systems<br/>Testing of APEX's CFRP and GFRP body tubes<br/><br/></h2>
          <p><br/><a href="ICLRResources/ASTRA3.mp4">ASTRA Mk.III, 10.07.2022 (MRC event)</a></p>
          <h2>Successful validation of in-house avionics systems<br/>Testing and validation of in-house separation system<br/>Testing and validation of in-house recovery system<br/>Investigations into live telemetry and in-flight video recording capabilities<br/>Further testing of launcher system with improvements to prevent fin strikes<br/><br/></h2>
          <p><br/><br/></p>
      </div>
  </div>
</main>