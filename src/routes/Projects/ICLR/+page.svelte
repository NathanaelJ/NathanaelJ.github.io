<script>
  import { base } from '$app/paths';
</script>

<svelte:head>
  <title>Rocketry | N Jenkins</title>
</svelte:head>

<main class="site-main">
  <div class="wrapper">
      <div class="page-header fade-in-up liquid-glass">
          <h1>Imperial College London Rocketry</h1>
          <p>The Altitude Record Team (ART) is a project within <a href="https://imperialrocketry.com" target="_blank" rel="noreferrer noopener">Imperial College London Rocketry (ICLR)</a> which exists to break <a href="https://ukra.ork.uk" target="_blank" rel="noreferrer noopener">United Kingdom Rocketry Association (UKRA)</a> altitude records. The team formed in 2019, with its first two launches in early 2021, and our first record-breaking flight in 2022.<br/><br/></p>
          
          <p>From 2020-2023, I led the aerodynamics and simulations sub-team, using computational methods to model and optimise the behaviour of our rocket. We used tools including <a href="https://openrocket.info" target="_blank" rel="noreferrer noopener">OpenRocket</a>, <a href="https://www.plm.automation.siemens.com/global/en/products/simcenter/STAR-CCM.html" target="_blank" rel="noreferrer noopener">StarCCM+</a>, and <a href="https://engineering.esteco.com/modefrontier/" target="_blank" rel="noreferrer noopener">ESTECO modeFrontier</a>.</p>
      </div>

      <div class="project-section fade-in-up liquid-glass" style="animation-delay: 1.0s;">
        <h3>Flight videos</h3>
        
        <div class="download-buttons" style="margin-bottom: 0px;">
            <a href="{base}/Projects/ICLRResources/ASTRA.mp4" target="_blank" rel="noreferrer noopener" class="download-btn liquid-glass">ASTRA Mk.I, 11.04.2021 (EARS event)</a>
            <a href="{base}/Projects/ICLRResources/ASTRA2.mp4" target="_blank" rel="noreferrer noopener" class="download-btn liquid-glass">ASTRA Mk.II, 13.06.2021 (EARS event)</a>
            <a href="{base}/Projects/ICLRResources/APEX.mp4" target="_blank" rel="noreferrer noopener" class="download-btn liquid-glass">APEX I, 03.07.2022 (Supported by SARA)</a>
            <a href="{base}/Projects/ICLRResources/ASTRA3.mp4" target="_blank" rel="noreferrer noopener" class="download-btn liquid-glass">ASTRA Mk.III, 10.07.2022 (MRC event)</a>
        </div>
    </div>

    <div class="project-section fade-in-up liquid-glass" style="animation-delay: 0.8s;">
        <h3>modeFrontier</h3>
        <p><a href="https://engineering.esteco.com/modefrontier/" target="_blank" rel="noreferrer noopener">ESTECO</a> kindly provided ICL Rocketry with licenses to use their powerful multidisciplinary optimisation (MDO) software, modeFrontier. This connects with many engineering modelling packages and can be used to optimise complex designs in much shorter timeframes, and with much greater control over simulations, than our previous methods. The team successfully used it to break the I-Class record with APEX-I.</p>
        
        <div class="download-buttons" style="margin-bottom: 0px;">
            <a href="ICLRResources/oR_mF/oRmFIntegration.pdf" target="_blank" rel="noreferrer noopener" class="download-btn liquid-glass">openRocket-modeFrontier Integration</a>
            <a href="ICLRResources/oR_mF/NSGA_HYBRID.pdf" target="_blank" rel="noreferrer noopener" class="download-btn liquid-glass">NSGA-HYBRID Performance Evaluation</a>
        </div>
    </div>
      
    <div class="project-section fade-in-up liquid-glass" style="animation-delay: 0.4s;">
        <h3>ASTRA</h3>
        <p>This is a family of test-bed rockets used to verify systems in preparation for record-breaking flights. Three successful flights took place during my tenure, testing progressively more advanced systems. The family has continued to be used for increasingly complex test flights.</p>
        
        <div class="image-container liquid-glass">
            <img src="{base}/Projects/ICLRResources/ASTRA.png" alt="ASTRA Family">
        </div>
    </div>

    <div class="project-section fade-in-up liquid-glass" style="animation-delay: 0.6s;">
        <h3>APEX</h3>
        <p>The APEX family of rockets are designed to break UKRA altitude records for various motor classes. Rocket motors are classified based on their total impulse (essentially a measure of the 'amount of push' they provide). The ICLR Altitude Record Team now holds the record for an I-Class rocket as of 2024.</p>
        
        <p><b>APEX I</b> reached 9333ft (3845m) with a single motor, breaking the previous record of 9199ft. It travelled at supersonic speeds (Mach 1.55) thanks to its highly optimised design.</p>
        
        <div class="image-container liquid-glass">
            <img src="{base}/Projects/ICLRResources/APEXI.png" alt="APEX I">
        </div>
    </div>
  </div>
</main>